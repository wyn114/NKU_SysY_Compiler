@array = global [10 x i32] [i32 5, i32 2, i32 9, i32 3, i32 8, i32 1, i32 7, i32 6, i32 4, i32 10], align 4 ; 全局整型数组声明

; 定义函数 int findNthLargest(int n, i32* array, i32 length)
define i32 @findNthLargest(i32 %n, i32* %array, i32 %length) {
entry:
  ; 为局部变量分配内存
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %max = alloca i32, align 4
  %temp = alloca i32, align 4

  ; 初始化循环计数器 i 和 j
  store i32 0, i32* %i, align 4
  store i32 0, i32* %j, align 4

  ; 循环开始处
  br label %loop_start

loop_start:
  ; 加载循环计数器 i 和 j
  %i_val = load i32, i32* %i, align 4
  %j_val = load i32, i32* %j, align 4

  ; 比较 i 和 n
  %cmp = icmp slt i32 %i_val, %n
  br i1 %cmp, label %loop_body, label %loop_exit

loop_body:
  ; 计算数组元素的地址
  %array_ptr = getelementptr inbounds [10 x i32], [10 x i32]* %array, i32 0, i32 %i_val
  %array_val = load i32, i32* %array_ptr, align 4

  ; 获取当前最大值
  %max_val = load i32, i32* %max, align 4

  ; 比较当前元素和当前最大值
  %cmp2 = icmp sgt i32 %array_val, %max_val
  br i1 %cmp2, label %update_max, label %next_iteration

update_max:
  ; 更新最大值
  store i32 %array_val, i32* %max, align 4

next_iteration:
  ; 更新循环计数器 i 和 j
  %i_val_next = add nsw i32 %i_val, 1
  store i32 %i_val_next, i32* %i, align 4
  %j_val_next = add nsw i32 %j_val, 1
  store i32 %j_val_next, i32* %j, align 4

  ; 回到循环开始处
  br label %loop_start

loop_exit:
  ; 返回第 n 大的数
  %max_val_final = load i32, i32* %max, align 4
  ret i32 %max_val_final
}

; 定义主函数 int main()
define i32 @main() {
entry:
  ; 为局部变量分配内存
  %n = alloca i32, align 4
  %result = alloca i32, align 4

  ; 从输入获取 n
  %n_val = call i32 @getint()
  store i32 %n_val, i32* %n, align 4

  ; 调用 findNthLargest 函数并存储结果
  %n_val_loaded = load i32, i32* %n, align 4
  %array_ptr = getelementptr inbounds [10 x i32], [10 x i32]* @array, i32 0, i32 0
  %result_val = call i32 @findNthLargest(i32 %n_val_loaded, i32* %array_ptr, i32 10)
  store i32 %result_val, i32* %result, align 4

  ; 打印结果
  %result_val_final = load i32, i32* %result, align 4
  call void @putint(i32 %result_val_final)

  ; 返回 0
  ret i32 0
}

; 函数声明
declare i32 @getint()
declare void @putint(i32)

