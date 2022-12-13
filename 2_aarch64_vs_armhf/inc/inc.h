#pragma once

/*
Process Y = M*X  + C
*/

void lib_api_process_data_c(int* pX, int* pM, int* pC, int* pY, int len);

#if ARM_NEON == 1
void lib_api_process_data_intrinsics(int* pX, int* pM, int* pC, int* pY, int len);
#endif

