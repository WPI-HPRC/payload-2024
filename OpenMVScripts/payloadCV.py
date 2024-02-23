# CV Filter - By: paigerust - Sat Dec 9 2023

import sensor, image, time, machine, pyb

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA) #QQVGA frame size: 160x120
sensor.skip_frames(time = 2000)


clock = time.clock()
start = pyb.millis()

m = mjpeg.Mjpeg('test_launch1.mjpeg')

with open("time_stamps.txt", "wb") as f:
    while(True):
        clock.tick()
        img = sensor.snapshot()
        m.add_frame(img)

        img.lens_corr(strength = 1.5)
        blob_size = []

        f.write("%d\n" % pyb.elapsed_millis(start))

        img.mode(7)

        blobs = img.find_blobs([(180, 255), (180, 255)], merge = True) # Detects all blobs with an average color lighter than 180

        if len(blobs) > 0:
            for blob in blobs: # Appends the blob size of each blob to the array blob_size, in total number of pixels
                blob_size.append(blob.pixels())

            for blob in blobs:
                if blob.pixels() == max(blob_size): #
                    optimal_blob = blob

            # Draw ellipse and crosshairs for optimal_blob
            img.draw_ellipse(optimal_blob.enclosed_ellipse(), color = (255, 255, 255))
            img.draw_cross(optimal_blob.cx(), optimal_blob.cy(), color = (0, 0, 0))

            # Print optimal_blob centroid to terminal
            # print("Blob centroid: " + str(optimal_blob.cx()) + ", " + str(optimal_blob.cy()))
        time.sleep(0.1)

        if pyb.elapsed_millis(start) > 18000:

            m.close(clock.fps())
            break

