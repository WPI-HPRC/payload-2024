# I2CTest - By: kai - Sun Feb 11 2024

import sensor, image, time, utime, rpc, struct, pyb

interface = rpc.rpc_i2c_slave(slave_addr=0x12)

clock = time.clock()
utime.sleep_ms(1000)

cx = 80
cy = 60

dat_buf = struct.pack("<ii",cx,cy)

while(True):
    #clock.tick()
    #img = sensor.snapshot()
    print(clock.fps())
    try:
        print("Trying Send")
        interface.put_bytes(dat_buf, timeout_ms=10)
    except OSError as e:
        pass
