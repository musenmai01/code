# ballCapture

ボールの検出アルゴリズムの開発コード

## ポイント
artExplosionに対して，OSCを用いて以下の情報が送信される．

+ ボールが検出されたかどうか
+ ボールの位置情報

## 操作方法

基本的には左上のnear/farのパラメータを調整する．

nearからfarまでの間の領域のデプスに物体がある場合に反応するように設定するためのものです．(これはカメラを正面においた場合の話ですが) 基本的にはfarは壁から少し手前にして，nearの値をどの程度にすると(nearとfarの間をどの程度長くすると)ボールが反応するかどうかを微調整する必要があります．

+ 'l'キー: near/farパラメータのロード
+ 's'キー: near/farパラメータの保存

## 環境

Mac(Xcode)
openFrameworks v0.10.0

## 依存関係
+ ofxKinect
+ ofxGui
+ ofxOpenCV
