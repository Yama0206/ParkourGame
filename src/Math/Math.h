#pragma once

//ベクトルの加算
VECTOR AddVec(VECTOR _vec1, VECTOR _vec2);
VECTOR AddVec(VECTOR _vec1, float x = 0.0f, float y = 0.0f, float z = 0.0f);

//ベクトルの減算
VECTOR SubVec(VECTOR _vec1, VECTOR _vec2);

//ベクトルの生成
VECTOR VecCreate(VECTOR _start, VECTOR _end);

//ベクトルの長さを計算
float LongVec(VECTOR _vec);

//ベクトルを正規化する
VECTOR NormalizeVec(VECTOR _vec);

//ベクトルをスカラー倍する関数
VECTOR ScaleVec(VECTOR _vec, float scale);

//ベクトルを除算する関数
VECTOR DivVec(VECTOR _vec, float div);

//内積
float VecDot(VECTOR vec1, VECTOR vec2);

//外積
float VecCross2D(VECTOR vec1, VECTOR vec2);

//角度変換
float TransAngleToRadian(float Angle);

//ベクターの絶対値を返す
VECTOR Vabs(VECTOR vNum);

//2点間の距離と正規化
//2D
//第1引数, 1つ目のX座標  第2引数, 1つ目のY座標
//第3引数, 2つ目のX座標  第4引数, 2つ目のY座標
float VecTwoPoint2D(float x_1, float y_1, float x_2, float y_2);
//3D
//第1引数, 1つ目の座標　　第2引数, 2つ目の座標
float VecTwoPoint3D(VECTOR vec1, VECTOR vec2);
