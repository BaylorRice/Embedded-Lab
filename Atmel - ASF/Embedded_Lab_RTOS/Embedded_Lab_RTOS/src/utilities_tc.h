#ifndef UTILITIES_TC_H_
#define UTILITIES_TC_H_

struct waveconfig_t {
	/** Internal clock signals selection. */
	uint32_t ul_intclock;
	/** Waveform frequency (in Hz). */
	uint16_t us_frequency;
	/** Duty cycle in percent (positive).*/
	uint16_t us_dutycycle;
};

/** TC waveform configurations */
static const struct waveconfig_t gc_waveconfig[] = {
	{TC_CMR_TCCLKS_TIMER_CLOCK4, 178, 30},
	{TC_CMR_TCCLKS_TIMER_CLOCK3, 375, 50},
	{TC_CMR_TCCLKS_TIMER_CLOCK3, 800, 75},
	{TC_CMR_TCCLKS_TIMER_CLOCK2, 1000, 80},
	{TC_CMR_TCCLKS_TIMER_CLOCK2, 4000, 55}
};

#if (SAM4L)
/* The first one is meaningless */
static const uint32_t divisors[5] = { 0, 2, 8, 32, 128};
#else
/* The last one is meaningless */
static const uint32_t divisors[5] = { 2, 8, 32, 128, 0};
#endif

/** Current wave configuration*/
static uint8_t gs_uc_configuration = 0;

/** Number of available wave configurations */
const uint8_t gc_uc_nbconfig = sizeof(gc_waveconfig)
/ sizeof(struct waveconfig_t);

/** Capture status*/
static uint32_t gs_ul_captured_pulses;
static uint32_t gs_ul_captured_ra;
static uint32_t gs_ul_captured_rb;

uint32_t ra, rc;

static void tc_waveform_initialize(void)
{
	

	/* Configure the PMC to enable the TC module. */
	sysclk_enable_peripheral_clock(ID_TC_WAVEFORM);

	/* Init TC to waveform mode. */
	tc_init(TC, TC_CHANNEL_WAVEFORM,
	/* Waveform Clock Selection */
	TC_CMR_TCCLKS_TIMER_CLOCK4
	| TC_CMR_WAVE /* Waveform mode is enabled */
	| TC_CMR_ACPA_SET /* RA Compare Effect: set */
	| TC_CMR_ACPC_CLEAR /* RC Compare Effect: clear */
	| TC_CMR_CPCTRG /* UP mode with automatic trigger on RC Compare */
	);

	/* Configure waveform frequency and duty cycle. */
	rc = (sysclk_get_peripheral_bus_hz(TC) /
	divisors[TC_CMR_TCCLKS_TIMER_CLOCK4]) /
	50;
	tc_write_rc(TC, TC_CHANNEL_WAVEFORM, rc);
	ra = (100 - 3) * rc / 100;
	tc_write_ra(TC, TC_CHANNEL_WAVEFORM, ra);

	/* Enable TC TC_CHANNEL_WAVEFORM. */
	tc_start(TC, TC_CHANNEL_WAVEFORM);

}

void change_duty_cycle(uint32_t duty_cycle)
{
	//uint32_t ra = 0;
	ra = (100 - duty_cycle) * rc / 100;
	tc_write_ra(TC, TC_CHANNEL_WAVEFORM, ra);
}

#endif /* UTILITIES_TC_H_ */