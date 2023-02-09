# Thuật toán Gomory giải quy hoạch nguyên toàn phần và quy hoạch nguyên hỗn hợp

## Cách sử dụng

Chương trình giải quyết bài toán sau:

$$ \min<\boldsymbol{c}, \boldsymbol{x}> \quad \text{s.t.} \quad \boldsymbol{Ax} = \boldsymbol{b}, \boldsymbol{x} \in D $$

Để giải bài toán, gọi hàm ```IntegerSimplex(A, b, c, starting_point, integer_type = "full", integer_pos = None, penalty_index = None)``` với các tham số sau:
* `A`: Ma trận $\boldsymbol{A}$
* `b`: Vector $\boldsymbol{b}$
* `c`: Vector $\boldsymbol{c}$ chỉ hệ số hàm mục tiêu
* `starting_point`: Danh sách chỉ số của phương án cực biên xuất phát tạo thành cơ sở đơn vị. LLưu ý danh sách này đánh chỉ số từ 0
* `integer_type`: Biến quyết định loại bài toán. Có 2 lựa chọn:
    * `"full"`: Giải bài toán quy hoạch nguyên toàn phần với $D = \mathbb{Z}^n$, $n$ là số chiều của \boldsymbol{x}
    * `"mixed"`: Giải bài toán quy hoạch nguyên hỗn hợp với $D = \mathbb{Z}^k \times \mathbb{R}^{n-k}$, $n$ là số chiều của \boldsymbol{x}
* `integer_pos`: Danh sách chỉ số của các biến cần nguyên. Lưu ý đánh chỉ số từ 0 và khi `integer_type = "full"`, tham số này không cần thiết
* `penalty_index`: Danh sách chỉ số của các biến phạt. Lưu ý đánh chỉ số từ 0

Các ví dụ và cài đặt bài toán được trình bày chi tiết trong file `gomory.ipynb`.


## Ưu điểm và hạn chế

* Ưu điểm
    * Chương trình sẽ đưa ra lời giải chi tiết cho bài toán với các chỉ số đánh số từ 1
    * Hỗ trợ kiểu in phân số với thư viện `Fractional` có sẵn trong Python

* Nhược điểm
    * Hiện tại chương trình chỉ test với trường hợp bài toán chắc chắn có nghiệm. 
    * Việc đánh chỉ số chưa thống nhất giữa input và output


## Tác giả

Bùi Tiến Thành ([@bu1th4nh](https://www.facebook.com/bu1th4nh.127/))
