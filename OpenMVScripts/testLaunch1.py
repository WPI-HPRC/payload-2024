# CV Filter - By: paigerust - Sat Dec 9 2023

import sensor, image, time, utime, rpc, machine, pyb, struct, mjpeg, math

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA) #QQVGA frame size: 160x120
sensor.skip_frames(time = 2000)

interface = rpc.rpc_i2c_slave(slave_addr=0x12)

clock = time.clock()
utime.sleep_ms(1000)

oblob_cx_count = 0
oblob_cy_count = 0
oblob_num = 0

count = 0
start = pyb.millis()

while True:
    loopTime = pyb.millis()
    m = mjpeg.Mjpeg('IREC2024%s.mjpeg' % count)
    with open("time_stamps%s.txt" % count, "wb") as f:
        with open("coordinates%s.txt" % count,"wb") as f2:
            with open("oscillations%s.txt" % count,"wb") as f3:

                while(pyb.elapsed_millis(loopTime) < 30000):
                    clock.tick()
                    img = sensor.snapshot()
                    m.add_frame(img)

                    img.lens_corr(strength = 1.5)
                    blob_size = []
                    oblob_cx = []
                    oblob_cy = []

                    f.write("%d\n" % pyb.elapsed_millis(start))

                    img.mode(7)

                    oblob_cx_count = 0
                    oblob_cy_count = 0
                    oblob_num = 0
                    oscstart = pyb.millis()

                    while(pyb.elapsed_millis(oscstart) < 1000):
                        blobs = img.find_blobs([(180, 255), (180, 255)], merge = True) # Detects all blobs with an average color lighter than 180

                        if len(blobs) > 0:
                            for blob in blobs: # Appends the blob size of each blob to the array blob_size, in total number of pixels
                                blob_size.append(blob.pixels())

                            for blob in blobs:
                                if blob.pixels() == max(blob_size): #
                                    optimal_blob = blob

                                    oblob_cx.append(optimal_blob.cx())
                                    oblob_cy.append(optimal_blob.cy())

                                    if len(oblob_cx) > 1: # AKA, if there have been at least two different blob centroids recorded

                                        # Compute the difference in centroid values between the current time slice and the previous time slice
                                        oblob_cx_diff = oblob_cx[-1] - oblob_cx[-2]
                                        oblob_cy_diff = oblob_cy[-1] - oblob_cx[-2]

                                        # Capture the difference in centroid values of the optimal blobs, adding up over a period of 1 second
                                        oblob_cx_count = oblob_cx_count + oblob_cx_diff
                                        oblob_cy_count = oblob_cy_count + oblob_cy_diff

                                        oblob_num = oblob_num + 1
                        
                    # Find the average difference in centroid values over a period of 1 second
                    osc_cx = oblob_cx_count/oblob_num
                    osc_cy = oblob_cy_count/oblob_num

                    # Calculate a "vector" quantity for the difference in centroids
                    osc_rate = math.sqrt((osc_cx**2) + (osc_cy**2))
                    f3.write("%d\n" % osc_rate)

                    # Draw ellipse and crosshairs for optimal_blob
                    img.draw_ellipse(optimal_blob.enclosed_ellipse(), color = (255, 255, 255))
                    img.draw_cross(optimal_blob.cx(), optimal_blob.cy(), color = (0, 0, 0))
                    f2.write("%d\t%d\n" % (optimal_blob.cx(), optimal_blob.cy()))


                    dat_buf = struct.pack("<ii",optimal_blob.cx(),optimal_blob.cy())

                    # Print optimal_blob centroid to terminal
                    print("Blob centroid: " + str(optimal_blob.cx()) + ", " + str(optimal_blob.cy()))

                    try:
                        print("Trying Send")
                        interface.put_bytes(dat_buf, timeout_ms=10)
                    except OSError as e:
                        pass

                    time.sleep(0.1)

                m.close()
                count += 1

