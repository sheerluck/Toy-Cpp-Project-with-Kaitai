meta:
  id: mp4
  endian: be
  license: WTF
  ks-version: 0.9

seq:

  - id: magic
    contents: [0x6d, 0x76, 0x68, 0x64]
  - id: version
    type: u1
  - id: flags
    size: 3
  - id: ctime
    type: u4
  - id: mtime
    type: u4
  - id: scale
    type: u4
  - id: duration
    type: u4

