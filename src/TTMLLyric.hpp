#ifndef TTMLLYRIC_H
#define TTMLLYRIC_H

#include <QDebug>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

typedef struct LyricWord {
    string word;
    int start;
    int end;
} LyricWord;

typedef struct LyricLine {
    vector<LyricWord> words;
    string translatedLyric;
    string romanLyric;
    bool isBG;
    bool isDuet;
    uint64_t startTime;
    uint64_t endTime;
} LyricLine;

/// @brief 一个用于存储和读取 TTML 歌词数据的类
class TTMLLyric {
public:
    TTMLLyric();
    ~TTMLLyric();
    /// @brief 清空所有数据，用于新建或读取新的文件
    void clear();
    /// @brief 从 TTML 字符串读取歌词行，并覆盖已有数据
    /// @param data 需要读取的 TTML 字符串
    void readFromString(string data);
    /// 解析出来的每个歌词行
    vector<LyricLine> lines = vector<LyricLine>();
    /// 歌词的元数据
    vector<tuple<string, vector<string>>> metadata = vector<tuple<string, vector<string>>>();
};

#endif // TTMLLYRIC_H
