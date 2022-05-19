# Snake Update - Game Project for INT2215

    Bài tập môn LTNC - INT2215 1
    Mã sinh viên: 21020392


## *Hướng dẫn cài đặt game*

1. Tải file exe.
1. Copy các file .dll trong file exe dán vào trong thư mục "C:\Windows\System32".
1. Bấm vào SnakeUpdate.exe trong file exe để bắt đầu chơi.

## *Mô tả trò chơi*

### *Giới thiệu*

* Snake Update là một trò chơi lấy ý tưởng thì trò chơi rắn săn mồi cổ điển. Nếu như rắn săn mồi chỉ đơn thuần là một người chơi ăn đồ ăn thì Snake Update là phiên bản hai người chơi thi đấu với nhau.
* Snake Update lấy bối cảnh ở ngoài vũ trụ - nơi có các thiên thạch, việc của các người chơi là điều khiển cho chú rắn của mình tránh khỏi các thiên thạch xung quanh chúng và tránh ăn các quả bom.


### *Cách chơi*

#### 1. Giới thiệu nhân vật
*  **Người chơi thứ nhất** điều khiển **con rắn màu xanh** ![HeadA](https://user-images.githubusercontent.com/100295385/169099720-14de0b98-d51c-44d5-a990-729df3bebe7c.png)
. Khi bắt đầu vào trò chơi, con rắn này ở phía trên của màn hình.
* **Người chơi thứ hai** điều khiển **con rắn màu cam** ![HeadB](https://user-images.githubusercontent.com/100295385/169099810-7ba073b0-d372-4779-9932-6a17693af035.png)
. Khi bắt đầu vào trò chơi, con rắn này ở vị trí dưới của màn hình.

#### 2. Luật chơi
* Hai người chơi điều khiển con rắn của mình sao cho không va chạm vào các thiên thạch xung quanh.
* Sau một khoảng thời gian nhất định, sẽ xuất hiện **lọ thuốc sức mạnh** ![Power](https://user-images.githubusercontent.com/100295385/169100452-1fce128c-3ea5-4c8a-9df2-e6de3c7a945a.png)
, và lọ thuốc này cũng chỉ xuất hiện trong một thời gian nhất định. Hãy cố gắng ăn lọ thuốc này và sử dụng nó (cụ thể sức mạnh ở phiên bản này là **đặt bom** ![bomb3](https://user-images.githubusercontent.com/100295385/169100247-999ff95e-764d-4619-9739-0cf4fa30aab8.png)
 trước mặt con rắn đối thủ).
* Ăn đúng thức ăn, rắn sẽ dài thêm một đốt. Nếu ăn phải bom, rắn sẽ bị giảm đi một đốt.
* Nếu người chơi để con rắn có độ dài nhỏ hơn 2 hoặc va chạm vào tường thì trận đấu kết thúc.
* Lưu ý: Người chơi chỉ được lưu 1 sức mạnh một lúc trong mình.

#### 3. Các phím thao tác
* Hai người chơi sử dụng bàn phím máy tính để điều khiển con rắn của mình.

    | Chức năng  | Player A | Player B|
    | ------------- |:-------------:| --------|
    | Di chuyển sang trái    | A    |← |
    | Di chuyển sang phải    | D    |→ |
    | Di chuyển lên trên     | W    |↑ |
    | Di chuyển xuống dưới   | S    |↓ |
    | Sử dụng chức năng ăn được | E |SPACE|
* Các thao tác trò chơi
    * Dừng/Tiếp tục trò chơi: sử dụng phím P, hoặc nhấn nút Pause/Continue.
    * Khởi động lại trò chơi: sử dụng phím N, hoặc nhấn nút Restart.
    * Bật/Tắt âm thanh: Nhấn nút Mute/Unmute.
    * Menu: Dùng thao tác chuột để chọn Play, Help, hay Exit.


## *Hình ảnh minh họa*

### Start Menu
![StartMenu](https://user-images.githubusercontent.com/100295385/168999915-977d73b4-4034-4a1b-954e-2ef6896370d3.jpg)

### Drop Bomb Function
![DropBomb](https://user-images.githubusercontent.com/100295385/169004838-fc1ff857-56b5-497d-8c61-251fcb5376dd.jpg)

### More
* [Video demo trò chơi](https://youtu.be/n7dh1LJjzY4)

## *Các kĩ thuật sử dụng*
### SDL
* Sử dụng các kĩ thuật để render hình ảnh, âm thanh.
* Load hình ảnh, âm thanh đơn giản.
* Sử dụng các kĩ thuật để xoay, cắt hình ảnh để giảm số lượng hình ảnh đầu vào.

### C++
* Sử dụng các kiến thức về: Mảng, Vector, Class, Struct, Random,...
* Sử dụng phân chia file để quản lí từng Game Object.

### Kĩ thuật khác
* Tính toán, căn chỉnh vị trí các đối tượng hiển thị.
* Phân chia file: Logic game ở một file và SDL ở một file.
* Tạo menu cùng các chức năng: Restart, Pause, Continue, Mute, Unmute.
* Tối giản hàm main dễ dọc, dễ hiểu.

## *Nguồn tham khảo*
* Nguồn hình ảnh, âm thanh: [FreePik](https://www.freepik.com/), tự thiết kế, ...
* Thư viện SDL2: [Lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php).
* Phân chia, quản lí file và logic game: do giáo viên thực hành hướng dẫn và tự lập trình lại.

## *Kết luận*
* Sau quá trình làm game, em rút ra được việc phân chia, quản lí các đối tượng hết sức quan trọng. Việc phân chia tốt sẽ giúp giảm thời gian sửa lỗi và dễ quản lí.
* Trong quá trình phát triển thêm chức năng Power cho rắn, em đã tạo một class Power để chứa các chức năng này. Điều này giúp các phiên bản sau, không chỉ có chức năng thả bom mà còn có thể dễ dàng thêm các chức năng mới và cải thiện các chức năng cũ. 

## *Lời cuối*
*Cảm ơn mọi người đã đọc và đánh giá project đầu tiên của em/mình.*

#### **Mức điểm tự đánh giá: 9 - 9,25.**
