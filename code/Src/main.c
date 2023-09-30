#include "main.h"
#include "tim.h"
#include "uart.h"
#include "gpio.h"
#include "motor.h"

void SystemClock_Config(void);

enum __attribute__((packed)) cmd_id {
    CMD_RESET = 1,
    CMD_TEST = 2,
    CMD_LED_TOGGLE,
    CMD_AZ_SET_K,
    CMD_EL_SET_K,
    CMD_SET_ORIGIN,
    CMD_STOP,
    CMD_AZ_STOP,
    CMD_EL_STOP,
    CMD_AZ_OFFSET,
    CMD_EL_OFFSET,
    CMD_AZ_GET_POS,
    CMD_EL_GET_POS,
    CMD_GET_POS,
};

struct cmd {
    uint16_t id;
    int16_t arg;
} cmd;

static void cmd_work(struct cmd cmd)
{
    switch (cmd.id) {
    case CMD_RESET: {
        NVIC_SystemReset();
    } break;
    case CMD_STOP: {
        motor_stop();
    } break;
    case CMD_AZ_STOP: {
        motor_az_stop();
    } break;
    case CMD_EL_STOP: {
        motor_el_stop();
    } break;
    case CMD_LED_TOGGLE: {
        gpio_led_toggle();
    } break;
    case CMD_AZ_OFFSET: {
        motor_az_offset(cmd.arg);
    } break;
    case CMD_EL_OFFSET: {
        motor_el_offset(cmd.arg);
    } break;
    case CMD_AZ_SET_K: {
        motor_az_set_k(cmd.arg);
    } break;
    case CMD_EL_SET_K: {
        motor_el_set_k(cmd.arg);
    } break;
    case CMD_AZ_GET_POS: {
        cmd.arg = motor_az_get_pos();
        UART_Send_Array(&cmd, sizeof(cmd));
    } break;
    case CMD_EL_GET_POS: {
        cmd.arg = motor_el_get_pos();
        UART_Send_Array(&cmd, sizeof(cmd));
    } break;
    case CMD_SET_ORIGIN: {
        motor_origin();
    } break;

    default:
        break;
    }
}

int main(void)
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    NVIC_SetPriority(SysTick_IRQn,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));

    SystemClock_Config();

    MX_GPIO_Init();
    MX_TIM10_Init();
    MX_TIM11_Init();
    UART_Init();

    LL_TIM_EnableCounter(TIM10);

    while (1) {
        static uint32_t led_cnt = 0;
        if (led_cnt++ > 0x7FFFFF) {
            led_cnt = 0;
            gpio_led_toggle();
        }

        if (uart_rx.is_new_data) {
            uart_rx.is_new_data = 0;
            struct cmd cmd = *(struct cmd *)&uart_rx.data;
            cmd_work(cmd);
        }
    }
}

void SystemClock_Config(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2) {
    }
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE2);
    LL_RCC_HSE_Enable();

    /* Wait till HSE is ready */
    while (LL_RCC_HSE_IsReady() != 1) {
    }
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 336,
                                LL_RCC_PLLP_DIV_4);
    LL_RCC_PLL_Enable();

    /* Wait till PLL is ready */
    while (LL_RCC_PLL_IsReady() != 1) {
    }
    while (LL_PWR_IsActiveFlag_VOS() == 0) {
    }
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    /* Wait till System clock is ready */
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    }
    LL_Init1msTick(84000000);
    LL_SetSystemCoreClock(84000000);
    LL_RCC_SetTIMPrescaler(LL_RCC_TIM_PRESCALER_TWICE);
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
