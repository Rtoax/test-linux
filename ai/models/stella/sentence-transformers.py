#!/bin/env python

# 对于短对短数据集，下面是通用的使用方式
from sentence_transformers import SentenceTransformer

sentences = ["数据1", "数据2"]
model = SentenceTransformer('fengshan/stella-base-zh')
print(model.max_seq_length)
embeddings_1 = model.encode(sentences, normalize_embeddings=True)
embeddings_2 = model.encode(sentences, normalize_embeddings=True)
similarity = embeddings_1 @ embeddings_2.T
print(similarity)
# 如果是短对长数据集，推荐添加instruction，来帮助模型更好地进行检索。
# 注意instruction里的是英文的冒号
