#pragma once

/*
Process Y = M*X  + C
*/

void lib_api_process_data_c(float* pX, float* pM, float* pC, float* pY, int len);

#if ARM_NEON == 1
void lib_api_process_data_intrinsics(float* pX, float* pM, float* pC, float* pY, int len);
#endif

