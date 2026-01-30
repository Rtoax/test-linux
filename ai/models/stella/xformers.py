#!/bin/env python

from modelscope import AutoModel, AutoTokenizer
from sklearn.preprocessing import normalize

model = AutoModel.from_pretrained('fengshan/stella-base-zh')
tokenizer = AutoTokenizer.from_pretrained('fengshan/stella-base-zh')
sentences = ["数据1", "数据ABCDEFGH"]
batch_data = tokenizer(
    #batch_text_or_text_pairs=sentences,
    text=sentences,
    padding="longest",
    return_tensors="pt",
    max_length=1024,
    truncation=True,
)
attention_mask = batch_data["attention_mask"]
model_output = model(**batch_data)
last_hidden = model_output.last_hidden_state.masked_fill(~attention_mask[..., None].bool(), 0.0)
vectors = last_hidden.sum(dim=1) / attention_mask.sum(dim=1)[..., None]
vectors = normalize(vectors, norm="l2", axis=1, )
print(vectors.shape)  # 2,768
