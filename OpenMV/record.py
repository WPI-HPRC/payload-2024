# Record - By: cbsco - Sat Dec 9 2023
#This is the initial recording script utilized for the parachute drop tests on 12-9-2023

import sensor, image, time, pyb, mjpeg

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE) #RGB565
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

m = mjpeg.Mjpeg('openmv_video2.mjpeg')

clock = time.clock()
start = pyb.millis()
with open("time_stamps.txt", "wb") as f:
    while(True):
        clock.tick()
        f.write("%d\n" % pyb.elapsed_millis(start))
        m.add_frame(sensor.snapshot())
        print(clock.fps())
        if pyb.elapsed_millis(start) > 1000000:
            print('over')
            #print(time)
            m.close(clock.fps())
            break
