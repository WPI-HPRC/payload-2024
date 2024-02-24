# CV Filter - By: paigerust - Sat Dec 9 2023
# Edited By: Kai Davidson - Sun Feb 11 2024

COLOR_THRESHOLDS = [(180, 255), (180, 255)] # Grayscale thresholds (min, max), consider abstracting this from "find_blobs" function call
TIMEOUT_MS = 10 # Timeout for I2C communication
PERIPHERAL_ADDR = 0x12 # I2C address of the peripheral

import sensor, image, time, machine, pyb, utime, rpc, struct

# Set up I2C interface
interface = rpc.rpc_i2c_slave(slave_addr=PERIPHERAL_ADDR)

# Set up camera sensor
sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA) #QQVGA frame size: 160x120
sensor.skip_frames(time = 2000)

# Set up timing
clock = time.clock()
start = pyb.millis()

# Set up MJPEG stream
m = mjpeg.Mjpeg('test_launch1.mjpeg')

# Main loop
with open("time_stamps.txt", "wb") as f:
    while(True):
        # Update timing
        clock.tick()
        # Capture image
        img = sensor.snapshot()
        # Add frame to MJPEG stream
        m.add_frame(img)

        #img.lens_corr(strength = 1.5)
        img.lens_corr(strength = 1.5)
        blob_size = []

        # Write time stamp to file
        f.write("%d\n" % pyb.elapsed_millis(start))

        img.mode(7)

        # Find blobs
        blobs = img.find_blobs([(180, 255), (180, 255)], merge = True) # Detects all blobs with an average color lighter than 180

        # If blobs are found, find the largest blob, no offense but you can do this in one loop over, just sort the blobs by size
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

            # This is the centroid data packet that will be sent to the payload
            optimal_blob_centroid = struct.pack("<ii", optimal_blob.cx(), optimal_blob.cy())

            # Check the polling rate is correct
            try:
                print("Trying Send")
                interface.put_bytes(optimal_blob_centroid, timeout_ms=TIMEOUT_MS)
            except OSError as e:
                pass

        time.sleep(0.1)

        if pyb.elapsed_millis(start) > 18000:

            m.close(clock.fps())
            break