// ModelManager.h
#include "../RenderUtility/Model.h"
#include <unordered_map>

/**
 * @brief モデルデータの管理を行う
 */
class ModelManager
{
public:
	/**
	 * @brief モデルデータを読み込む
	 * @param filePath モデルデータへのファイルパス
	 * @return モデルへのポインタ(shared_ptr)
	 */
	static std::shared_ptr<Model> Load(const std::string& filePath);

	/**
	 * @brief 使用していないモデルデータを解放する
	 */
	static void CollectGarbage();

	/**
	 * @brief 全てのモデルデータを解放する
	 */
	static void Clear();

private:
	ModelManager() = delete;

	/// ファイルパスとモデルデータのマップ
	static std::unordered_map<std::string, std::shared_ptr<Model>> s_models;
};