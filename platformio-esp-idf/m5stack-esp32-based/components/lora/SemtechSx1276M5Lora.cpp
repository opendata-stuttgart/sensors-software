/**
 * \file SemtechSx1276M5Lora.cpp
 * \author greenairalsace.vercel.app (m.alognikou, d.kalumvuati, r.nguemo and a.azzoug)
 * \brief The main purpose of this component is to implement function to work with lora
 *        protocol based on semtech sx1276 sensor for M5 series board
 * \date 11 may 2023
 * \copyright all rigth reserved to greenairalsace.vercel.app
 */


/**********************************************************************************************************************/
/* INCLUSIONS                                                                                                         */
/**********************************************************************************************************************/

#include "SemtechSx1276M5Lora.h"

/**********************************************************************************************************************/
/* PRIVATE VARIABLES                                                                                                  */
/**********************************************************************************************************************/

static SPISettings sx1276_lora_spi_settings(8E6, MSBFIRST, SPI_MODE0);

/**********************************************************************************************************************/
/* PRIVATE METHODS CODE                                                                                               */
/**********************************************************************************************************************/

/**
 * @brief put the sx1276 lora device in sleep mode.
 * The register in used is REG_OP_MODE.
 * bit7 = LongRangeMode (0 => FSK/OOK, 1 => Lora)
 * bit6-5 = ModulationType (00 => FSK, 01 => OOK)
 * bit4 = reserved
 * bit3 = LowFrequencyModeOn (0 => High freq, 1 Low freq)
 * bit2-0 = Mode (000 => sleep, 001 => standby)
 *
 * @retval null (void)
*/
extern "C" void m5_sx1276_lora_sleep_mode() {
    // 0x80 = 1000 0000
    m5_esp32_spi_write(REG_OP_MODE, 0x80, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
}

/**
 * @brief put the sx1276 lora device in standby mode.
 * The register in used is REG_OP_MODE.
 * bit7 = LongRangeMode (0 => FSK/OOK, 1 => Lora)
 * bit6-5 = ModulationType (00 => FSK, 01 => OOK)
 * bit4 = reserved
 * bit3 = LowFrequencyModeOn (0 => High freq, 1 Low freq)
 * bit2-0 = Mode (000 => sleep, 001 => standby)
 *
 * @retval null (void)
*/
extern "C" void m5_sx1276_lora_standby_mode() {
    // 0x80 = 1000 0001
    m5_esp32_spi_write(REG_OP_MODE, 0x80 | 0x01, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
}

/**
 * @brief set the sx1276 lora device carrier frequency
 * Registers in used are REG_FRF_MSB, REG_FRF_MID and REG_FRF_LSB
 * The formula giving by the datasheet is device_freq * 32MHZ / 2^19
 * 
 * @param dev_freq device work frequency
 * 
 * @retval void
*/
extern "C" void m5_sx1276_lora_set_carrier_freq(long dev_freq) {
    uint64_t frf = ((uint64_t)dev_freq << 19) / 32000000;

    m5_esp32_spi_write(REG_FRF_MSB, (uint8_t)(frf >> 16), M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
    m5_esp32_spi_write(REG_FRF_MID, (uint8_t)(frf >> 8), M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
    m5_esp32_spi_write(REG_FRF_LSB, (uint8_t)(frf >> 0), M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
}

/**
 * @brief set the sx1276 lora device output power
 * The register in used is REG_PA_CONFIG
 * The advice from the datasheet is to work between 2db - 17db for data performance
 * bit7 = 1 for PA_BOOST pin. Output power is limited to +20 dBm
 * bit6-4 = MaxPower (Select max output power: Pmax=10.8+0.6*MaxPower [dBm])
 * bit3-0 = OutputPower (formula is Pout=17-(15-OutputPower) if PaSelect = 1 (PA_BOOST pin))
 * 
 * @param output_power The outpout power
 * 
 * @retval null (void)
*/
extern "C" void m5_sx1276_lora_set_tx_power_paBoostPin(int output_power) {
    if (output_power < 2) {
        output_power = 2;
    } else if (output_power > 17) {
        output_power = 17;
    }

    m5_esp32_spi_write(REG_PA_CONFIG, 0x80 | (output_power -(15 - output_power)), M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
}

/**
 * @brief set the sx1276 lora device modem payload header mode to explicit
 * The register in used is REG_MODEM_CONFIG_1
 * bit7-4 = Signal bandwidth: 0000 => 7.8 kHz
 * bit3-1 = coding rate: 001 => 4/5
 * bit0 = 0 => Explicit Header mode
 * 
 * @retval null (void)
*/
extern "C" void m5_sx1276_lora_set_modem_explicit_mode() {
    m5_esp32_spi_write(REG_MODEM_CONFIG_1, m5_esp32_spi_read(REG_MODEM_CONFIG_1, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings) & 0xfe, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
}

/**********************************************************************************************************************/
/* PUBLIC METHODS CODE                                                                                                */
/**********************************************************************************************************************/

extern "C" bool m5_sx1276_lora_turn_on(long dev_freq) {
    // set the chip select pin
    pinMode(M5_SX1276_LORA_CHIP_SELECT_PIN, OUTPUT);

    // set the chip select pin to high
    digitalWrite(M5_SX1276_LORA_CHIP_SELECT_PIN, HIGH);

    // perform full reset of the sensor device (for safety and efficiency purpose)
    if (M5_SX1276_LORA_RESET_PIN != -1) {
        pinMode(M5_SX1276_LORA_RESET_PIN, OUTPUT);

        digitalWrite(M5_SX1276_LORA_RESET_PIN, LOW);
        delay(10);
        digitalWrite(M5_SX1276_LORA_RESET_PIN, HIGH);
        delay(10);
    }

    // start SPI
    m5_esp32_spi_start();

    // test the SPI commmunication by checking the Semtech ID relating the silicon revision
    uint8_t version = m5_esp32_spi_read(REG_VERSION, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
    if (version != 0x12) {
        return false;
    }

    // put in sleep mode
    m5_sx1276_lora_sleep_mode();

    // set frequency
    m5_sx1276_lora_set_carrier_freq(dev_freq);

    // set the FIFO base addresses (size of FIFO is 64 bytes)
    m5_esp32_spi_write(REG_FIFO_TX_BASE_ADDR, 0x00, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
    m5_esp32_spi_write(REG_FIFO_RX_BASE_ADDR, 0x00, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);

    // set LNA boost
    // Boost on, 150% LNA current (boost high freq)
    m5_esp32_spi_write(REG_LNA, m5_esp32_spi_read(REG_LNA, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings) | 0x03, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);

    // set auto AGC
    // The AGC feature allows receiver to handle a wide Rx input dynamic range from the sensitivity level up to maximum input 
    // level of 0dBm or more, whilst optimizing the system linearity.
    // summary : for low data rate optimized
    m5_esp32_spi_write(REG_MODEM_CONFIG_3, 0x04, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);

    // set output power to 17 dBm
    m5_sx1276_lora_set_tx_power_paBoostPin(17);

    // put in standby mode
    m5_sx1276_lora_standby_mode();

    return true;
}

extern "C" void m5_sx1276_lora_turn_off() {
    m5_sx1276_lora_sleep_mode();
    m5_esp32_spi_stop();
}

extern "C" bool m5_sx1276_lora_data_session_open() {
    // put in standby mode
    m5_sx1276_lora_standby_mode();

    // configure the payload (preambule + sync word + lenght byte + addr byte + message + CRC)
    m5_sx1276_lora_set_modem_explicit_mode();

    // reset FIFO address and paload length for handling new data
    m5_esp32_spi_write(REG_FIFO_ADDR_PTR, 0x00, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
    m5_esp32_spi_write(REG_PAYLOAD_LENGTH, 0x00, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);

    return true;
}

extern "C" bool m5_sx1276_lora_data_session_close() {
    // put in TX (transmitter) mode
    m5_esp32_spi_write(REG_OP_MODE, 0x83, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);

    // wait for TX done
    while ((m5_esp32_spi_read(REG_IRQ_FLAGS, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings) & 0x08) == 0) {
        yield();
    }

    // clear IRQ's
    m5_esp32_spi_write(REG_IRQ_FLAGS, 0x08, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);

    return true;
}


extern "C" int m5_sx1276_lora_analyze_packet_get_size() {
   return m5_sx1276_lora.parsePacket();
}

extern "C" size_t m5_sx1276_lora_data_transfer(const uint8_t* data_buff, size_t data_size) {
    int currentLength = m5_esp32_spi_read(REG_PAYLOAD_LENGTH, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);

    // check size
    // message maximum size accroding to the datasheet is 255 bytes
    if ((currentLength + data_size) > 255) {
        data_size = 255 - currentLength;
    }

    Serial.print("data size");
    Serial.print(data_size);

    // write data
    for (size_t i = 0; i < data_size; i++) {
        Serial.println(data_buff[i]);
        m5_esp32_spi_write(REG_FIFO, data_buff[i], M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);
    }

    // update length
    m5_esp32_spi_write(REG_PAYLOAD_LENGTH, currentLength + data_size, M5_SX1276_LORA_CHIP_SELECT_PIN, sx1276_lora_spi_settings);

    return data_size;
}

extern "C" int m5_sx1276_lora_data_process() {
   return m5_sx1276_lora.available();
}

extern "C" int m5_sx1276_lora_get_data() {
   return m5_sx1276_lora.read();
}

/**********************************************************************************************************************/
/* END OF FILE                                                                                                        */
/**********************************************************************************************************************/