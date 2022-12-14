#pragma once

/*
Process Y = M*X  + C
*/

void lib_process_api_c(float* pX, float* pM, float* pC, float* pY, int len);

#if ARM_NEON == 1
void lib_process_api_intrinsics(float* pX, float* pM, float* pC, float* pY, int len);
#endif

