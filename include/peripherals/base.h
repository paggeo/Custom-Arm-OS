#ifndef	_P_BASE_H
#define	_P_BASE_H

#if (MODEL_3 == MODEL)
	/** For raspi 2,3: PBASE = 0x3F000000 */
	#define PBASE 0x3F000000
#elif (MODEL_4 == MODEL)
	/** For raspi 4:    PBASE= 0xFE000000 */
	#define PBASE 0xFE000000
#endif

#endif  /*_P_BASE_H */
