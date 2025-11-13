#include "Audio.h"
#include "Main.h"
#include "Stage.h"
#include "UI.h"

StageManager stageManager;

void StageManager::SetUp() {
	cityHandle = MV1LoadModel("Resource/Stages/city.mv1");
	carHandle[0] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_1.mv1");
	carHandle[1] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_2.mv1");
	carHandle[2] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_3.mv1");
	carHandle[3] = MV1LoadModel("Resource/Stages/SmallCars/SmallCar_4.mv1");
	carHandle[4] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_1.mv1");
	carHandle[5] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_2.mv1");
	carHandle[6] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_3.mv1");
	carHandle[7] = MV1LoadModel("Resource/Stages/LargeCars/LargeCar_4.mv1");

	cloudHandle[0] = MV1LoadModel("Resource/Stages/Clouds/Cloud_1.mv1");
	cloudHandle[1] = MV1LoadModel("Resource/Stages/Clouds/Cloud_2.mv1");
	cloudHandle[2] = MV1LoadModel("Resource/Stages/Clouds/Cloud_3.mv1");
	cloudHandle[3] = MV1LoadModel("Resource/Stages/Clouds/Cloud_4.mv1");
	cloudHandle[4] = MV1LoadModel("Resource/Stages/Clouds/Cloud_5.mv1");

	CarsSetUp();
	CloudsSetUp();

	// コンストラクタでモデルを設定できないのでここでモデルを設定する
	for (int i = 1; i < MAX_STAGE_NUM; i++) {
		for (int j = 0; j < carArray[i].size(); j++) {
			carArray[i][j].SetCarHandle(carHandle[carArray[i][j].GetCarHandle()]);
		}
		for (int k = 0; k < cloudArray[i].size(); k++) {
			cloudArray[i][k].SetCloudHandle(cloudHandle[cloudArray[i][k].GetCloudHandle()]);
		}
	}

	// モデルの光の当たり方を設定：DXライブラリの初期設定のままだと暗すぎるので明るくする
	for (int i = 0; i < MV1GetMaterialNum(cityHandle); i++)	// ステージのモデル
	{
		MV1SetMaterialDifColor(cityHandle, i, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
		MV1SetMaterialAmbColor(cityHandle, i, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
		MV1SetMaterialSpcColor(cityHandle, i, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
		MV1SetMaterialEmiColor(cityHandle, i, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
		MV1SetMaterialSpcPower(cityHandle, i, 3.0f);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < MV1GetMaterialNum(carHandle[i]); j++) {
			MV1SetMaterialDifColor(carHandle[i], j, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
			MV1SetMaterialAmbColor(carHandle[i], j, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
			MV1SetMaterialSpcColor(carHandle[i], j, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
			MV1SetMaterialEmiColor(carHandle[i], j, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
			MV1SetMaterialSpcPower(carHandle[i], j, 3.0f);
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < MV1GetMaterialNum(cloudHandle[i]); j++) {
			MV1SetMaterialDifColor(cloudHandle[i], j, GetColorF(0.8f, 0.8f, 0.8f, 1.0f));
			MV1SetMaterialAmbColor(cloudHandle[i], j, GetColorF(0.9f, 0.9f, 0.9f, 0.9f));
			MV1SetMaterialSpcColor(cloudHandle[i], j, GetColorF(0.2f, 0.2f, 0.2f, 0.2f));
			MV1SetMaterialEmiColor(cloudHandle[i], j, GetColorF(0.3f, 0.3f, 0.3f, 0.0f));
			MV1SetMaterialSpcPower(cloudHandle[i], j, 3.0f);
		}
	}
}

void StageManager::CarsSetUp() {
	// ステージ1の車の描画情報
	{
		carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 3000));
		carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 5000));
		carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 7000));
		carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 11000));
		carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 13000));
		carArray[1].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 16000));
		carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 17700));
		carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 19200));
		carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 20800));
		carArray[1].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 22300));
	}
	// ステージ2の車の描画情報
	{
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 3000));
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 5000));
		carArray[2].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 8000));
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 9700));
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 11200));
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 12700));
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 16500));
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 18500));
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 20500));
		carArray[2].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 23500));
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 24700));
		carArray[2].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 26200));
	}
	// ステージ3の車の描画情報
	{
		carArray[3].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 3000));
		carArray[3].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 5000));
		carArray[3].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 7000));
		carArray[3].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 9000));
		carArray[3].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 12000));
		carArray[3].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 13700));
		carArray[3].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 15200));
		carArray[3].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 16700));
		carArray[3].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 18200));
		carArray[3].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 23000));
	}
	// ステージ4の車の描画情報
	{
		carArray[4].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 4000));
		carArray[4].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 7000));
		carArray[4].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 11500));
		carArray[4].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 14500));
		carArray[4].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 17300));
		carArray[4].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 21500));
		carArray[4].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 23500));
		carArray[4].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 25500));
	}
	// ステージ5の車の描画情報
	{
		carArray[5].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 3000));
		carArray[5].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 6000));
		carArray[5].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 8500));
		carArray[5].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 15000));
		carArray[5].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 19000));
		carArray[5].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 22000));
	}
	// ステージ6の車の描画情報
	{
		carArray[6].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 3000));
		carArray[6].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 4200));
		carArray[6].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 8500));
		carArray[6].push_back(Car(SmallCarModelRandom(), S_CAR_HEIGHT, S_CAR_RADIUS, 10000));
		carArray[6].push_back(Car(LargeCarModelRandom(), L_CAR_HEIGHT, L_CAR_RADIUS, 12000));
	}
}

void StageManager::CloudsSetUp() {	// メモ　小じゃん隙間　600
	// ステージ1の雲の描画情報
	{
		cloudArray[1].push_back(Cloud(CloudModelRandom(), -480));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), -240));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 0));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 240));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 480));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 720));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 960));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 1200));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 1440));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 1680));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 1920));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 2160));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 2400));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 2640));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 2880));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 3120));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 3360));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 3600));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 3840));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 4080));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 4320));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 4560));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 4800));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 5040));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 5280));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 5520));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 5760));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 6000));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 6240));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 6480));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 6720));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 6960));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 7200));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 7440));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 7680));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 7920));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 8160));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 8400));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 8640));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 8880));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 9120));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 9360));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 9600));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 9840, true));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 10440));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 10680));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 10920));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 11160));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 11400));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 11640, true));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 12240));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 12480));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 12720));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 12960));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 13200));
		cloudArray[1].push_back(Cloud(CloudModelRandom(), 13440, true));
	}
	// ステージ2の雲の描画情報
	{
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 3360));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 3600));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 3840));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 4080));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 4320));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 4560));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 4800));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 5040));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 5280));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 5520));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 5760));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 6000, true));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 6600));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 6840));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 6840));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 7080));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 7320));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 7560, true));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 12000));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 12240));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 12480));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 12720));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 12960));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 13200));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 13440));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 13680));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 13920));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 14160, true));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 14760));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 15000));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 15240));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 15480));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 15720));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 15960));
		cloudArray[2].push_back(Cloud(CloudModelRandom(), 16200, true));
	}
	// ステージ3の雲の描画情報
	{
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 5520));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 5760));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 6000));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 6240));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 6480));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 6720));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 6960));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 7200));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 7440));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 7680));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 7920, true));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 8520));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 8760));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 9000));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 9240));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 9480, true));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 10080));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 10320));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 10560));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 10800));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 11040));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 11280, true));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 12480));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 12720));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 12960));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 13200));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 13440));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 13680));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 13920));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 14160));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 14400));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 14640));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 14880));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 15120));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 15360));
		cloudArray[3].push_back(Cloud(CloudModelRandom(), 15600));
	}
	// ステージ4の雲の描画情報
	{
		cloudArray[4].push_back(Cloud(CloudModelRandom(), -480));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), -240));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 0));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 240));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 480));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 720));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 960));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 1200));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 1440));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 1680));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 1920));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 2160));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 2400));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 2640));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 2880, true));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 3480));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 3720));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 3960));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 4200));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 4440));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 4680, true));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 6960));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 7200));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 7440));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 7680));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 7920));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 8160));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 8400));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 8640, true));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 9240));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 9480));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 9720));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 9960));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 10200));
		cloudArray[4].push_back(Cloud(CloudModelRandom(), 10440, true));
	}
	// ステージ5の雲の描画情報
	{
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 2400));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 2640));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 2880));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 3120));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 3360));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 3600));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 3840, true));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 4440));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 4680));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 4920));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 5160));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 5400));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 5640, true));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 7680));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 7920));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 8160));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 8400));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 8640));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 8880));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 9120, true));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 11760));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 12000));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 12240));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 12480));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 12720));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 12960));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 13200));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 13440));
		cloudArray[5].push_back(Cloud(CloudModelRandom(), 13680, true));
	}
	// ステージ6の雲の描画情報
	{
		cloudArray[6].push_back(Cloud(CloudModelRandom(), -480));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), -240));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 0));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 240));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 480));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 720));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 960));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 1200));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 1440));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 1680));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 1920, true));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 2420));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 2660));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 2900));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 3140));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 3380, true));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 5520));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 5760));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 6000));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 6240));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 6480));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 6720));
		cloudArray[6].push_back(Cloud(CloudModelRandom(), 6960));
	}
}



void StageManager::Draw(Player& _player) {
	bool test = false;
	// 背景ステージの描画と衝突判定の設定
	MV1DrawModel(cityHandle);
	if (IsCollision(_player, VGet(12000, 0, 0), 40, 20000, false, false))test = true;	// リファクタリング：ステージを全部作り終わったら定数に変更
	// 車の描画
	if (!base.GetIsGameStop()) carMoveX += -7;	// 車を左に移動させていく
	for (int i = 0; i < carArray[base.GetStageNumber()].size(); i++) {
		Car car = carArray[base.GetStageNumber()][i];	// 描画用に一時的に取得
		VECTOR drawPos = VAdd(car.GetPosition(), VGet(carMoveX, 0, 0));
		MV1SetPosition(car.GetCarHandle(), drawPos);	// 車の座標を更新
		MV1DrawModel(car.GetCarHandle());
		// 衝突したらゲームオーバーに設定
		if (!base.GetIsGameStop() && IsCollision(_player, drawPos, car.GetHeight(), car.GetRadius(), true, false)) {
			fadeManager.ChangeUIState(GAMEOVER, NOTFADE);
			audioManager.PlaySE(audioManager.JINGLE_GAMEOVER);
		}
	}

	// 雲の描画

	for (int j = 0; j < cloudArray[base.GetStageNumber()].size(); j++) {
		Cloud cloud = cloudArray[base.GetStageNumber()][j];
		MV1SetPosition(cloud.GetCloudHandle(), cloud.GetPosition());
		MV1DrawModel(cloud.GetCloudHandle());
		if (IsCollision(_player, cloud.GetPosition(), cloud.GetHeight(), cloud.GetRadius(), false, cloud.GetIsScoreAdd())) {
			test = true;
		}
	}

	_player.SetIsGround(test);
}

bool StageManager::IsCollision(Player& _player, const VECTOR& _objPos, float _height, float _radius, bool _isObstacles, bool _isCloudScoreAdd) {
	VECTOR playerPos = _player.GetPosition();
	VECTOR playerScale = _player.GetScale();
	bool collisionX = (playerPos.x + playerScale.x > _objPos.x - _radius) && (playerPos.x - playerScale.x < _objPos.x + _radius);	// X軸でプレイヤーがオブジェクトに衝突しているか判定
	bool collisionY = (_player.GetIsGravityBottom() && playerPos.y <= _objPos.y + _height && playerPos.y + playerScale.y >= _objPos.y) ||	// 下のオブジェクトならオブジェ上側よりプレイヤーが下か、上のオブジェクトならオブジェ下側よりプレイヤー上に居るか判定
		(!_player.GetIsGravityBottom() && playerPos.y >= _objPos.y + _height && playerPos.y - playerScale.y <= _objPos.y);

	//足場の判定
	if (!_isObstacles) {
		// プレイヤーがobj.xの範囲内にいてobj.yの範囲内にもいる場合設置判定を有効にする
		if (collisionX && collisionY) {
			_player.SetGroundPosY(_objPos.y + _height);	// 足場となる座標を保存
			float objRightDis = base.ClampNumF((_objPos.x + _radius) - playerPos.x, 0, 500);
			if (_isCloudScoreAdd && _player.CheckChangeJumpDis(objRightDis)) {
				_player.SetJumpDis(objRightDis);
			}
			return true;
		}
		// obj.yの範囲内にいるがobj.xの範囲外にいる場合はそのまま落下する
		else if (!collisionX && collisionY) {
			return false;
		}
	}
	// 車の判定
	else {
		float objLeftDis = base.ClampNumF((_objPos.x - _radius) - playerPos.x, 0, 500);
		if (collisionX && collisionY) return true;	// 車の中にプレイヤーが侵入したら
		else if (!collisionX && collisionY && _player.CheckChangeJumpDis(objLeftDis)) {
			_player.SetJumpDis(objLeftDis);
		}
	}
	return false;
}

bool StageManager::IsClear(float _playerPosX) {
	return _playerPosX >= GOAL_POS_X[base.GetStageNumber()] + CLEAR_CHANGE_DIS;	// ゴール後一定以上進んだらクリア画面の遷移を可能にするフラグをtrueにする
}

void StageManager::Initialization() {
	carMoveX = 0;	// 車の移動座標の初期化
	// 背景ステージの座標をステージに合わせて変更
	cityDrawPos.z = CITY_POS_Z[base.GetStageNumber()];
	MV1SetPosition(cityHandle, cityDrawPos);
}