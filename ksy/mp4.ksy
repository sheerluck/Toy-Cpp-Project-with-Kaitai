meta:
  id: mp4
  endian: be
  license: WTF
  ks-version: 0.9

seq:

  - id: magic
    contents: [0x44, 0x89]
  - id: protocol
    type: u1
    enum: size_type
  - id: value4
    type: f4
    if: protocol == size_type::float
  - id: value8
    type: f8
    if: protocol == size_type::double

enums:
  size_type:
    0x84: float
    0x88: double

