#pragma GCC push_options
#pragma GCC optimize ("O0")

static inline void _nop_(void) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

static inline void setSDA(int v) {
    HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,v);
}

static inline void setSCK(int v) {
    HAL_GPIO_WritePin(SCK_GPIO_Port,SCK_Pin,v);
}

static inline void setDC(int v) {
    HAL_GPIO_WritePin(DC_GPIO_Port,DC_Pin,v);
}
static inline void setCS(int v) {
    HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,v);
}
static inline void setRES(int v) {
    HAL_GPIO_WritePin(RES_GPIO_Port,RES_Pin,v);
}
#pragma pop_options