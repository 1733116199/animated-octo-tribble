import zlib

CRCPOLY = 0xEDB88320
CRCINV = 0x5B358FD3
INITXOR = 0xFFFFFFFF
FINALXOR = 0xFFFFFFFF

def blah(bs, desired_hash):

    desired_hash = desired_hash ^ FINALXOR
    old_hash = zlib.crc32(bs) ^ FINALXOR

    suffix = 0

    for i in range(0, 32):
        if(suffix & 1 != 0):
            suffix = (suffix >> 1) ^ CRCPOLY
        else:
            suffix = suffix >> 1
        if(desired_hash & 1 != 0):
            suffix = suffix ^ CRCINV
        desired_hash = desired_hash >> 1

    suffix = suffix ^ old_hash

    buffer = bytearray([0, 0, 0, 0])
    for i in range(0, 4):
        buffer[i] = (suffix >> i * 8) & 0xFF
    
    return buffer

sid = b'12345678'
hash = zlib.crc32(sid)
suffix = blah(sid, hash)

print(f"Your sid is {sid}. Its hex representation is {sid.hex()}. Its hash is {hash:x}.")
print(f"The new byte array is {sid.hex() + suffix.hex()}. Its hash is also {zlib.crc32(sid + suffix):x}")
