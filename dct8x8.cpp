//https://godbolt.org/z/ehYjWjWoE

inline void dct8(float x0, float x1, float x2, float x3, float x4, float x5,
                 float x6, float x7, float &y0, float &y1, float &y2, float &y3,
                 float &y4, float &y5, float &y6, float &y7) {
    float temp8;
    float temp0 = x0 + x7;
    float temp4 = (x0 - x7) * float(0.5097955791041592);
    float temp1 = x1 + x6;
    float temp5 = (x1 - x6) * float(0.6013448869350453);
    float temp2 = x2 + x5;
    float temp6 = (x2 - x5) * float(0.8999762231364156);
    float temp3 = x3 + x4;
    float temp7 = (x3 - x4) * float(2.5629154477415055);
    x0 = temp0 + temp3;
    x2 = (temp0 - temp3) * float(0.5411961001461970);
    x1 = temp1 + temp2;
    x3 = (temp1 - temp2) * float(1.3065629648763764);
    temp0 = x0 + x1;
    temp1 = (x0 - x1) * float(0.7071067811865475);
    x0 = temp0;
    x1 = temp1;
    temp0 = x2 + x3;
    temp1 = (x2 - x3) * float(0.7071067811865475);
    x2 = temp0;
    x3 = temp1;
    temp0 = x0;
    temp1 = x2 + x3;
    temp2 = x1;
    temp3 = x3;
    x0 = temp4 + temp7;
    x2 = (temp4 - temp7) * float(0.5411961001461970);
    x1 = temp5 + temp6;
    x3 = (temp5 - temp6) * float(1.3065629648763764);
    temp4 = x0 + x1;
    temp5 = (x0 - x1) * float(0.7071067811865475);
    x0 = temp4;
    x1 = temp5;
    temp4 = x2 + x3;
    temp5 = (x2 - x3) * float(0.7071067811865475);
    x2 = temp4;
    x3 = temp5;
    temp4 = x0;
    temp5 = x2 + x3;
    temp6 = x1;
    temp7 = x3;
    x0 = temp0;
    x1 = temp4 + temp5;
    x2 = temp1;
    x3 = temp5 + temp6;
    x4 = temp2;
    x5 = temp6 + temp7;
    x6 = temp3;
    x7 = temp7;
    // scale
    y0 = x0 * float(1.0 / 8);
    y1 = x1 * float(2.0 / 8);
    y2 = x2 * float(2.0 / 8);
    y3 = x3 * float(2.0 / 8);
    y4 = x4 * float(2.0 / 8);
    y5 = x5 * float(2.0 / 8);
    y6 = x6 * float(2.0 / 8);
    y7 = x7 * float(2.0 / 8);
}

inline void idct8(float x0, float x1, float x2, float x3, float x4, float x5,
                  float x6, float x7, float &y0, float &y1, float &y2,
                  float &y3, float &y4, float &y5, float &y6, float &y7) {
    float temp8;
    float tmp;
    float temp0 = x0;
    float temp4 = x1;
    float temp1 = x2;
    float temp5 = x1 + x3;
    float temp2 = x4;
    float temp6 = x3 + x5;
    float temp3 = x6;
    float temp7 = x5 + x7;
    x0 = temp0;
    x2 = temp1;
    x1 = temp2;
    x3 = temp1 + temp3;
    temp0 = x0;
    temp1 = x1;
    tmp = temp1 * float(0.7071067811865475);
    x0 = temp0 + tmp;
    x1 = temp0 - tmp;
    temp0 = x2;
    temp1 = x3;
    tmp = temp1 * float(0.7071067811865475);
    x2 = temp0 + tmp;
    x3 = temp0 - tmp;
    tmp = x2 * float(0.5411961001461970);
    temp0 = x0 + tmp;
    temp3 = x0 - tmp;
    tmp = x3 * float(1.3065629648763764);
    temp1 = x1 + tmp;
    temp2 = x1 - tmp;
    x0 = temp4;
    x2 = temp5;
    x1 = temp6;
    x3 = temp5 + temp7;
    temp4 = x0;
    temp5 = x1;
    tmp = temp5 * float(0.7071067811865475);
    x0 = temp4 + tmp;
    x1 = temp4 - tmp;
    temp4 = x2;
    temp5 = x3;
    tmp = temp5 * float(0.7071067811865475);
    x2 = temp4 + tmp;
    x3 = temp4 - tmp;
    tmp = x2 * float(0.5411961001461970);
    temp4 = x0 + tmp;
    temp7 = x0 - tmp;
    tmp = x3 * float(1.3065629648763764);
    temp5 = x1 + tmp;
    temp6 = x1 - tmp;
    tmp = temp4 * float(0.5097955791041592);
    y0 = temp0 + tmp;
    y7 = temp0 - tmp;
    tmp = temp5 * float(0.6013448869350453);
    y1 = temp1 + tmp;
    y6 = temp1 - tmp;
    tmp = temp6 * float(0.8999762231364156);
    y2 = temp2 + tmp;
    y5 = temp2 - tmp;
    tmp = temp7 * float(2.5629154477415055);
    y3 = temp3 + tmp;
    y4 = temp3 - tmp;
}


typedef float float8x8array[8][8];

void dct8x8(float8x8array &x) {
    for (int y = 0; y < 8; ++y) {
        dct8(x[y][0], x[y][1], x[y][2], x[y][3], x[y][4], x[y][5], x[y][6],
             x[y][7], x[y][0], x[y][1], x[y][2], x[y][3], x[y][4], x[y][5],
             x[y][6], x[y][7]);
    }
    for (int r = 0; r < 8; ++r) {
        dct8(x[0][r], x[1][r], x[2][r], x[3][r], x[4][r], x[5][r], x[6][r],
             x[7][r], x[0][r], x[1][r], x[2][r], x[3][r], x[4][r], x[5][r],
             x[6][r], x[7][r]);
    }
}

void idct8x8(float8x8array &x) {
    for (int r = 0; r < 8; ++r) {
        idct8(x[0][r], x[1][r], x[2][r], x[3][r], x[4][r], x[5][r], x[6][r],
              x[7][r], x[0][r], x[1][r], x[2][r], x[3][r], x[4][r], x[5][r],
              x[6][r], x[7][r]);
    }
    for (int y = 0; y < 8; ++y) {
        idct8(x[y][0], x[y][1], x[y][2], x[y][3], x[y][4], x[y][5], x[y][6],
              x[y][7], x[y][0], x[y][1], x[y][2], x[y][3], x[y][4], x[y][5],
              x[y][6], x[y][7]);
    }
}

