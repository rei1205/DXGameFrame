// VectorUtility.h
#pragma once
#include <vector>

/**
 * @brief vectorに対する拡張操作
 */
class VectorUtility
{
public:
    /**
     * @brief vectorの要素を移動させる
     * @param vec 移動を行うvectorへの参照
     * @param from 移動させる要素のインデックス
     * @param to 移動先のインデックス
     */
    template<typename T>
    static void MoveElement(std::vector<T>& vec, size_t from, size_t to)
    {
        if (from >= vec.size() || to > vec.size() || from == to)
            return;

        // 移動要素を退避
        T temp = std::move(vec[from]);
        vec.erase(vec.begin() + from);

        // 移動先補正
        if (from < to)
            --to;

        vec.insert(vec.begin() + to, std::move(temp));
    }

private:
    VectorUtility() = delete;
};
