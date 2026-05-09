uint16_t axpert_crc(const uint8_t *data, uint16_t len) {
    uint16_t crc = 0;
    for (uint16_t i = 0; i < len; i++) {
        uint8_t d = data[i];
        uint8_t da = ((uint8_t)(crc >> 8)) >> 4;
        crc <<= 4;
        static const uint16_t crc_table[] = {
            0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
            0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef
        };
        crc ^= crc_table[da ^ (d >> 4)];
        da = ((uint8_t)(crc >> 8)) >> 4;
        crc <<= 4;
        crc ^= crc_table[da ^ (d & 0x0f)];
      }
    return crc;
}
