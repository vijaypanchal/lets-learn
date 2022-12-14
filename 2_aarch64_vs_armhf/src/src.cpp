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
    float32x4_t c_32x3 = vld1q_dup_f32(pC);

    // 32 Elements in Loop
    while(size >= 32){
        for(int i = 0; i < 8 ; i++)
            input_32x4[i] = vld1q_f32(input+i*4);
        
        for(int i = 0; i < 8 ; i++)
            output_32x4[i] = vmulq_f32(input_32x4[i],m_32x4);
        
        for(int i = 0; i < 8 ; i++)
            output_32x4[i] = vaddq_f32(output_32x4[i],m_32x4);
        
        for(int i = 0; i < 8 ; i++)
            vst1q_f32(output+i*4,output_32x4[i]);        

        input+=32;
        output+=32;
        size-=32;        
    }

    // 16 Elements in Loop
    while(size >= 16){
        input_32x4[0] = vld1q_f32(input);
        input_32x4[1] = vld1q_f32(input+4);
        input_32x4[2] = vld1q_f32(input+8);
        input_32x4[3] = vld1q_f32(input+12);

        output_32x4[0] = vmulq_f32(input_32x4[0],m_32x4);
        output_32x4[1] = vmulq_f32(input_32x4[1],m_32x4);
        output_32x4[2] = vmulq_f32(input_32x4[2],m_32x4);
        output_32x4[3] = vmulq_f32(input_32x4[3],m_32x4);

        output_32x4[0] = vaddq_f32(output_32x4[0],m_32x4);
        output_32x4[1] = vaddq_f32(output_32x4[1],m_32x4);
        output_32x4[2] = vaddq_f32(output_32x4[2],m_32x4);
        output_32x4[3] = vaddq_f32(output_32x4[3],m_32x4);

        vst1q_f32(output,output_32x4[0]);
        vst1q_f32(output+4,output_32x4[1]);
        vst1q_f32(output+8,output_32x4[2]);
        vst1q_f32(output+12,output_32x4[3]);

        input+=16;
        output+=16;
        size-=16;        
    }


    // 8 Elements in Loop
    while(size >= 8){
        input_32x4[0] = vld1q_f32(input);
        input_32x4[1] = vld1q_f32(input+4);
        
        output_32x4[0] = vmulq_f32(input_32x4[0],m_32x4);
        output_32x4[1] = vmulq_f32(input_32x4[1],m_32x4);
        
        output_32x4[0] = vaddq_f32(output_32x4[0],m_32x4);
        output_32x4[1] = vaddq_f32(output_32x4[1],m_32x4);
        
        vst1q_f32(output,output_32x4[0]);
        vst1q_f32(output+4,output_32x4[1]);
        
        input+=8;
        output+=8;
        size-=8;        
    }

    while(size >= 4){
        input_32x4[0] = vld1q_f32(input);       

        output_32x4[0] = vmulq_f32(input_32x4[0],m_32x4);

        output_32x4[0] = vaddq_f32(output_32x4[0],m_32x4);        

        vst1q_f32(output,output_32x4[0]);

        input+=4;
        output+=4;
        size-=4;        
    }

    while(size>0){
        int i = 0;
        for(i = size; i >= 0; i--){
            pY[len-i] = pX[len-i]*M + C;
        }    
    }
}
#endif