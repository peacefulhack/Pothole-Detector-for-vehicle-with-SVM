#pragma once
#include <stdarg.h>
#include <stdint.h>

namespace Eloquent {
    namespace ML {
        namespace Port {
            class SVM {
                public:
                    /**
                    * buat Prediksi class untuk vektor tar bikin hyperplanenya
                    */
                    int predict(float *x) {
                        float kernels[19] = { 0 };
                        float decisions[3] = { 0 };
                        int votes[3] = { 0 };
                        kernels[0] = compute_kernel(x,   1139.0  , 1142.0  , 3.0 );
                        kernels[1] = compute_kernel(x,   1201.0  , 1205.0  , 4.0 );
                        kernels[2] = compute_kernel(x,   1161.0  , 1164.0  , 3.0 );
                        kernels[3] = compute_kernel(x,   1103.0  , 1107.0  , 4.0 );
                        kernels[4] = compute_kernel(x,   1107.0  , 1112.0  , 5.0 );
                        kernels[5] = compute_kernel(x,   1194.0  , 1197.0  , 3.0 );
                        kernels[6] = compute_kernel(x,   1203.0  , 1206.0  , 3.0 );
                        kernels[7] = compute_kernel(x,   1152.0  , 1160.0  , 8.0 );
                        kernels[8] = compute_kernel(x,   1136.0  , 1144.0  , 8.0 );
                        kernels[9] = compute_kernel(x,   1188.0  , 1196.0  , 8.0 );
                        kernels[10] = compute_kernel(x,   1187.0  , 1194.0  , 7.0 );
                        kernels[11] = compute_kernel(x,   1183.0  , 1190.0  , 7.0 );
                        kernels[12] = compute_kernel(x,   1178.0  , 1182.0  , 4.0 );
                        kernels[13] = compute_kernel(x,   1145.0  , 1152.0  , 7.0 );
                        kernels[14] = compute_kernel(x,   1165.0  , 1169.0  , 4.0 );
                        kernels[15] = compute_kernel(x,   1172.0  , 1176.0  , 4.0 );
                        kernels[16] = compute_kernel(x,   1179.0  , 1183.0  , 4.0 );
                        kernels[17] = compute_kernel(x,   1138.0  , 1142.0  , 4.0 );
                        kernels[18] = compute_kernel(x,   1137.0  , 1141.0  , 4.0 );
                        decisions[0] = 11.144542735601
                        + kernels[1] * 0.039292503985
                        + kernels[4] * 0.08126701956
                        + kernels[8] * -0.120559523545
                        ;
                        decisions[1] = 6.998745139258
                        + kernels[0] * 0.087809192601
                        + kernels[1]
                        + kernels[2] * 0.466246800092
                        + kernels[3]
                        + kernels[4]
                        + kernels[5] * 0.77926673975
                        + kernels[6]
                        + kernels[12] * -0.575131373084
                        - kernels[14]
                        + kernels[15] * -0.758191359359
                        - kernels[16]
                        - kernels[17]
                        - kernels[18]
                        ;
                        decisions[2] = -14.992604306142
                        + kernels[7] * 0.001633910099
                        + kernels[8] * 0.331033139223
                        + kernels[9]
                        + kernels[10] * -0.555330001208
                        + kernels[11] * -0.457226647147
                        + kernels[13] * -0.320110400967
                        ;
                        votes[decisions[0] > 0 ? 0 : 1] += 1;
                        votes[decisions[1] > 0 ? 0 : 2] += 1;
                        votes[decisions[2] > 0 ? 1 : 2] += 1;
                        int val = votes[0];
                        int idx = 0;

                        // cek prediksi terbesar
                        for (int i = 1; i < 3; i++) {
                            if (votes[i] > val) {
                                val = votes[i];
                                idx = i;
                            }
                        }

                        return idx;
                    }

                    /**
                    * baca data yg mo di predict dari user
                    */
                    const char* predictLabel(float *x) {
                        return idxToLabel(predict(x));
                    }

                    /**
                    * labelin 0: jalan aman, 1: jalan berlubang, 2: Jalan crack
                    */
                    const char* idxToLabel(uint8_t classIdx) {
                        switch (classIdx) {
                            case 0:
                            return "Jalan Aman";
                            case 1:
                            return "Jalan Berlubang";
                            case 2:
                            return "Jalan Crack";
                            default:
                            return "Error penamaan";
                        }
                    }

                protected:
                    /**
                    * Hitung kernel biar jadi vector satu nilai.
                    * Kernel tipe: linear
                    */
                    float compute_kernel(float *x, ...) {
                        va_list w;
                        va_start(w, 3);
                        float kernel = 0.0;

                        for (uint16_t i = 0; i < 3; i++) {
                            kernel += x[i] * va_arg(w, double);
                        }

                        return kernel;
                    }
                };
            }
        }
    }
