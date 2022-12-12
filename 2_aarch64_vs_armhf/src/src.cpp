

int lib_api_process_data(int* pX, int* pM, int* pC, int* pY, int len){
    int i = 0;
    int M = *pM;
    int C = *pM;
    for(i = 0; i < len; i++){
        pY[i] = pX[i]*M + C;
    }
    return 0;
}