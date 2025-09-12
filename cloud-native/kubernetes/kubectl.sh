#!/bin/bash

# 检查 kubectl 是否知道集群地址及凭证
kubectl config view

# 查看所有节点
kubectl get nodes

# 查看单个节点详细信息
kubectl describe node [NODE-NAME]

# 查看 Service 信息
kubectl get service

# 查看集群信息
kubectl cluster-info

# 查看 NS
kubectl get namespaces

# 查看 pods
kubectl get pods
kubectl describe pods
kubectl logs [POD-NAME]

# 执行 pod
kubectl exec [POD-NAME] env
kubectl exec -ti [POD-NAME] bash
