# BÀI TẬP BÃI ĐỖ XE
### Cho bài toán bãi gửi xe 2 bánh (xe đạp và xe máy) không qua đêm. Giá tiền gửi được xác định theo ban ngày và ban đêm.
-  Xe đạp, ban ngày: 1k vnd
-  Xe đạp, ban đêm : 2k vnd
-  Xe đạp đêm - ngày: 3k vnd
- Xe đạp đêm - ngày - đêm: 5k vnd
- Xe máy, ban ngày: 3k vnd
- Xe máy, ban đêm: 5k vnd
- Xe máy, đêm - ngày: 8k vend
- Xe máy, đêm - ngày - đêm: 13k vnd

Ban ngày từ 06:00:00 đến trước 18:00:00
Cho phép thực hiện một lệnh hoặc một chuỗi lệnh trên dữ liệu giữ xe. Các lệnh cho phép bao gồm:
1. list: in ra danh sách xe trong bãi, theo thứ tự của input. Lưu ý chỉ trả về biển số.
2. find <plate>: tìm xe có biển số <plate> có trong bãi hay không. Ví dụ: find 31K1-123.45: in ra chỉ số của xe trong danh sách nếu tìm thấy, -1 nếu không tìm thấy
3. in <hh:mm:ss> <plate>: lúc <hh:mm:ss> cho xe biển số <plate> vào bãi. Ví dụ: in 10:00:02 31K1-123.45 trả về 0 nếu lỗi (xe đang trong bãi), 1 nếu thành công
4. out <hh:mm:ss> <plate>: lúc <hh:mm:ss> cho xe biển số <plate> ra. Ví dụ: out 03:04:56 31K1-123.45 trả về 0 nếu lỗi (xe không có trong bãi), 1 nếu thành công
5. cnt-moto: đếm số xe máy đang có trong bãi
6. bill <hh:mm:ss> <plate>: tính tiền gửi xe cho xe có biển <plate>. nếu không tìm thấy xe trong bãi trả về -1. Chú ý, chỉ tính tiền, xe vẫn ở trong bãi, không cho xe ra khỏi bãi.
7. billall: tính tổng số tiền gửi xe thu được từ khi bắt đầu chạy chương trình, việc thu tiền được thực hiện khi xe ra khỏi bãi.


### Input
- Khối đầu tiên chứa thông tin về các lượt gửi xe được cho theo các dòng định dạng như sau:
<hh:mm:ss> <plate>: là xe có biển số <plate> đã vào bãi vào lúc <hh:mm:ss> của ngày hiện tại. Trường hợp xe đạp không biển số <plate> có giá trị xxxx-000.01 với 4 kí tự đầu luôn là xxxx, 5 số cuối là mã số của vé được phát.
- Kết thúc khối đầu tiên là 1 dòng chứa dấu *
- Khối thứ 2 chứa chuỗi các lệnh hoặc chuỗi lệnh, mỗi lệnh trên một hàng, kết thúc bằng dấu ***

### Output
Thực hiện một chuỗi các truy vấn trên dữ liệu đã cho bao gồm:
-  list: trả về danh sách xe trong bãi
- find 31K1-123.45
