#if ARM_NEON == 1
#include <arm_neon.h>
#endif
void lib_process_api_c(float* pX, float* pM, float* pC, float* pY, int len){
    int i = 0;
    float M = *pM;
    float C = *pM;
    for(i = 0; i < len; i++){
        pY[i] = pX[i]*M + C;
    }
}

#if ARM_NEON == 1
void lib_process_api_intrinsics(float* pX, float* pM, float* pC, float* pY, int len){
    
    float *input = pX;
    float *output = pY;
    float M = *pM;
    float C = *pM;
    int size = len;

    float32x4_t input_32x4[8];
    float32x4_t output_32x4[8];
    float32x4_t m_32x4 = vld1q_dup_f32(pM);
    float32x4_t c_32x4 = vld1q_dup_f32(pC);
    float32x2_t m_32x2 = vld1_dup_f32(pM);
    float32x2_t c_32x2 = vld1_dup_f32(pC);

    // 32 Elements in Loop
    while(size >= 32){
        for(int i = 0; i < 8 ; i++)
            input_32x4[i] = vld1q_f32(input+i*4);
        
        for(int i = 0; i < 8 ; i++)
            output_32x4[i] = vmulq_f32(input_32x4[i],m_32x4);
        
        for(int i = 0; i < 8 ; i++)
            output_32x4[i] = vaddq_f32(output_32x4[i],c_32x4);
        
        for(int i = 0; i < 8 ; i++)
            vst1q_f32(output+i*4,output_32x4[i]);        

        input+=32;
        output+=32;
        size-=32;        
    }

    // 16 Elements in Loop
    while(size >= 16){
        for(int i = 0; i < 4 ; i++)
            input_32x4[i] = vld1q_f32(input+i*4);
        
        for(int i = 0; i < 4 ; i++)
            output_32x4[i] = vmulq_f32(input_32x4[i],m_32x4);
        
        for(int i = 0; i < 4 ; i++)
            output_32x4[i] = vaddq_f32(output_32x4[i],c_32x4);
        
        for(int i = 0; i < 4 ; i++)
            vst1q_f32(output+i*4,output_32x4[i]);

        input+=16;
        output+=16;
        size-=16;        
    }


    // 8 Elements in Loop
    while(size >= 8){
        for(int i = 0; i < 2 ; i++)
            input_32x4[i] = vld1q_f32(input+i*4);
        
        for(int i = 0; i < 2 ; i++)
            output_32x4[i] = vmulq_f32(input_32x4[i],m_32x4);
        
        for(int i = 0; i < 2 ; i++)
            output_32x4[i] = vaddq_f32(output_32x4[i],c_32x4);
        
        for(int i = 0; i < 2 ; i++)
            vst1q_f32(output+i*4,output_32x4[i]);
        
        input+=8;
        output+=8;
        size-=8;        
    }
    // 4 Elements in Loop
    while(size >= 4){
        // Load pX[] 4 elements  pY[i] = pX[i]*M + C;
        input_32x4[0] = vld1q_f32(input);       
        // Multipication of 4 elemetns pX[i]*M
        output_32x4[0] = vmulq_f32(input_32x4[0],m_32x4);
        // Addition of 4 elements pX[i]*M + C
        output_32x4[0] = vaddq_f32(output_32x4[0],c_32x4);        
        // Storing  pY[] 4 elements 
        vst1q_f32(output,output_32x4[0]);

        input+=4;
        output+=4;
        size-=4;        
    }

    // 2 Elements in Loop
    while(size >= 2){
        // Load pX[] 2 elements  pY[i] = pX[i]*M + C;
        float32x2_t input_32x2 = vld1_f32(input);       
        // Multipication of 2 elemetns pX[i]*M
        float32x2_t output_32x2 = vmul_f32(input_32x2,m_32x2);
        // Addition of 2 elements pX[i]*M + C
        output_32x2 = vadd_f32(output_32x2,c_32x2);        
        // Storing  pY[] 2 elements 
        vst1_f32(output,output_32x2);

        input+=2;
        output+=2;
        size-=2;        
    }   
}
#endif