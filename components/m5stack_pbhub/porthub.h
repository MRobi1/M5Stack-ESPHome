#include "porthub.h"
#include "esphome/core/log.h"

namespace esphome {
namespace m5stack_pbhub {

static const char *const TAG = "m5stack_pbhub.porthub";

PortHub::PortHub() {
    this->set_i2c_address(IIC_ADDR1);
}

PortHub::PortHub(uint8_t iic_addr, i2c::I2CBus *i2c_bus) {
    this->set_i2c_address(iic_addr);
    this->set_i2c_bus(i2c_bus);
    this->_iic_addr = iic_addr;
}

void PortHub::begin() {
    ESP_LOGD(TAG, "Initializing PortHub at address 0x%02X", this->_iic_addr);
}

uint16_t PortHub::hub_a_read_value(uint8_t reg) {
    uint16_t value = 0;
    uint8_t data[2];
    
    if (this->read_register(reg, data, 2) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to read analog value from register 0x%02X", reg);
        return 0;
    }
    
    value = (data[0] << 8) | data[1];
    return value;
}

uint8_t PortHub::hub_d_read_value_A(uint8_t reg) {
    uint8_t value = 0;
    
    if (this->read_register(reg, &value, 1) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to read digital value A from register 0x%02X", reg);
        return 0;
    }
    
    return value;
}

uint8_t PortHub::hub_d_read_value_B(uint8_t reg) {
    uint8_t value = 0;
    
    if (this->read_register(reg + 1, &value, 1) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to read digital value B from register 0x%02X", reg + 1);
        return 0;
    }
    
    return value;
}

void PortHub::hub_d_wire_value_A(uint8_t reg, uint16_t level) {
    uint8_t data[2] = {(uint8_t)(level >> 8), (uint8_t)(level & 0xFF)};
    
    if (this->write_register(reg, data, 2) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to write digital value A to register 0x%02X", reg);
    }
}

void PortHub::hub_d_wire_value_B(uint8_t reg, uint16_t level) {
    uint8_t data[2] = {(uint8_t)(level >> 8), (uint8_t)(level & 0xFF)};
    
    if (this->write_register(reg + 2, data, 2) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to write digital value B to register 0x%02X", reg + 2);
    }
}

void PortHub::hub_a_wire_value_A(uint8_t reg, uint16_t duty) {
    uint8_t data[2] = {(uint8_t)(duty >> 8), (uint8_t)(duty & 0xFF)};
    
    if (this->write_register(reg, data, 2) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to write analog value A to register 0x%02X", reg);
    }
}

void PortHub::hub_a_wire_value_B(uint8_t reg, uint16_t duty) {
    uint8_t data[2] = {(uint8_t)(duty >> 8), (uint8_t)(duty & 0xFF)};
    
    if (this->write_register(reg + 2, data, 2) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to write analog value B to register 0x%02X", reg + 2);
    }
}

void PortHub::hub_wire_length(uint8_t reg, uint16_t length) {
    uint8_t data[2] = {(uint8_t)(length >> 8), (uint8_t)(length & 0xFF)};
    
    if (this->write_register(reg, data, 2) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to write wire length to register 0x%02X", reg);
    }
}

void PortHub::hub_wire_index_color(uint8_t reg, uint16_t num, uint8_t r, int8_t g, uint8_t b) {
    uint8_t data[5] = {
        (uint8_t)(num >> 8), 
        (uint8_t)(num & 0xFF), 
        r, 
        (uint8_t)g, 
        b
    };
    
    if (this->write_register(reg, data, 5) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to write index color to register 0x%02X", reg);
    }
}

void PortHub::hub_wire_fill_color(uint8_t reg, uint16_t first, uint16_t count, uint8_t r, int8_t g, uint8_t b) {
    uint8_t data[7] = {
        (uint8_t)(first >> 8), 
        (uint8_t)(first & 0xFF),
        (uint8_t)(count >> 8), 
        (uint8_t)(count & 0xFF),
        r, 
        (uint8_t)g, 
        b
    };
    
    if (this->write_register(reg, data, 7) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to write fill color to register 0x%02X", reg);
    }
}

void PortHub::hub_wire_setBrightness(uint8_t reg, uint8_t brightness) {
    if (this->write_register(reg, &brightness, 1) != i2c::ERROR_OK) {
        ESP_LOGW(TAG, "Failed to write brightness to register 0x%02X", reg);
    }
}

}  // namespace m5stack_pbhub
}  // namespace esphome
