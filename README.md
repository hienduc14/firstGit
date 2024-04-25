# Survivor (IAM SLIME)
- Cấu trúc code và thử nghiệm game: 
- Gameplay: 

## Giới thiệu 
Game survival nhiều màn chơi đa dạng, điều khiển Slime né tránh, giết quái, đánh boss

- [0. Cách tải game](#0-cách-tải-game)
- [1. Bắt đầu game](#1-bắt-đầu-game)
- [2. Các thành phần trong game](#2-các-thành-phần-trong-game)
  * [a. Người chơi](#a-người-chơi)
  * [b. Kẻ địch](#b-kẻ-địch)
  * [c. Khác](#c-khác)
- [3. Điều khiển và gameplay](#3-điều-khiển-và-gameplay)
- [4. Một vài hình ảnh trong game](#4-một-vài-hình-ảnh-trong-game)
- [5. Về source code của game](#5-về-source-code-của-game)

## 0. Cách tải game
**Bước 1:** Clone repo này về hoặc chọn Code -> Download Zip

**Bước 2:** Cài codeblocks-20.03mingw

**Bước 3:** Thêm các file SDL2.dll, SDL2_image.dll, SDL2_mixer.dll, SDL2_ttf.dll vào thư mục gốc.

**Bước 4:** Chạy file [Survivor.exe](Survivor.exe) hoặc mở file [Survivor.cbp](Survivor.cbp) và chạy game bằng phím F9

## 1. Bắt đầu game

- Màn hình chính:

![image](https://github.com/hienduc14/firstGit/blob/master/menu/Menu.png)

- Click vào nút "Play" để chọn map. Có 3 map:
  * Meadow: Thảo nguyên 
  * Graveyard: Nghĩa địa
  * Volcano: Núi lửa

- Chọn "Options" trên góc trên phải để cài đặt âm thanh và hiển thị sát thương
  * Âm thanh: có thể bật, tắt âm thanh, thay đổi độ lớn của nhạc nền(Music) và âm thanh hiệu ứng(Sound Effect)
  * DMG Numbers: Tắt/Bật hiển thị số sát thương gây ra
  * Exit: để thoát game.

- Chọn "Tutorial" để xem hướng dẫn các phím điều khiển

- Chọn "Shop" để mua các trang phục bằng tiền kiếm được trong game

## 2. Các thành phần trong game
### a. Người chơi
- Slime(Gundam) : là bọng nhớt do người chơi điều khiển, bị trừ máu nếu va chạm với kẻ địch hoặc kĩ năng của kẻ địch.
- Các loại kĩ năng chủ động:
  *  Jump :  Có thể nhảy qua quái và đạn, có thời gian hồi chiêu 3s.
  *  Kameha : nhấn giữ L để vận công và nhả L để bắn chưởng. Khi vẫn công sẽ đứng im, có thể điều chỉnh góc bắn bằng W S, có thể huỷ trong lúc vận bằng nhấn giữ núi O. Khi bắn chưởng, hi sinh 1/2 máu và đứng im.
- Các loại kĩ năng tự động:
  *  Orb : đạn bắn theo hướng di chuyển
  *  FireBall : đạn tự nhắm vào kẻ thù gần nhất
  *  Zone : toạ ra 1 vùng gây sát thương xung quanh slime

- Tăng cấp : khi nhặt đủ kinh nghiệm để lên cấp sẽ được chọn 1 trong 3 nâng cấp: nâng cấp kĩ năng tự động hoặc tăng chỉ số cá nhân

- Thông tin của Slime: 
  * Thanh máu: cho biết slime còn lại bao nhiêu phần máu
  * Thanh kinh nghiệm: cho biết slime cần tích thêm bao nhiêu phần kinh nghiệm để tăng cấp
### b. Kẻ địch
- Quái nhỏ: đa dạng quái nhỏ đến từ các hướng đuổi theo Slime, khiến Slime mất máu khi chạm vào Slime. Khi giết có tỉ lệ rơi DropItem
- Dropitem : các vật phẩm rơi ra khi giết quái nhỏ có thể hấp thụ
  * Exp: giúp Slime tăng cấp
  * Health: giúp Slime hồi máu
  * Coin: có thể dùng để mua hàng trong shop
- Slime lớn (Boss) : Slime loại boss cỡ lớn, lượng máu cao xuất hiện sau một thời gian ở map Meadow. Có kĩ năng nhắm vào người chơi và nhảy đến
- Ghost lớn (Boss) : Ghost loại boss có lượng máu cao, có khả năng triệu hồi các ghost nhỏ từ tất cả các hướng đuổi Slime
- FlameBoss (Boss) : Người lửa loại boss có lượng máu cao, có khả năng vận công và bắn chưởng lửa
- Thanh máu : Thanh máu của kẻ địch, hiện khi đối đầu với boss
### c. Khác
- KillCount: đếm đã giết được bao nhiêu quái
- TimeCount: đếm đã sinh tồn được bao lâu
- Nút tạm dừng (pause) : Click nút này sẽ tạm dừng trò chơi. Sau khi nhấn, hiện lên màn hình chờ như hình dưới, bao gồm các lựa chọn:
  * Tiếp tục trò chơi
  * Quay về nàn hình chính
  * Điều chỉnh âm thanh
  * Tắt/Bật hiển thị sát thương
  

## 3. Điều khiển và gameplay

- Các phím điều khiển:
  * Di chuyển: các phím W, A, S, D tương ứng với di chuyển lên, sang trái, xuống, sang phải
  * Jump: nhấn J để nhảy
  * Kameha: giữ L để vận và nhả L để bắn chưởng. Khi vẫn công sẽ đứng im, có thể điều chỉnh góc bắn bằng W S, có thể huỷ trong lúc vận bằng nhấn giữ nút O
- Về gameplay:
  * Trò chơi sẽ diễn ra theo nhiều đợt, mỗi đợt có tỉ lệ ra quái khác nhau và sau một số đợt thì boss xuất hiện. Nhiệm vụ của người chơi là sống sót, tiêu diệt boss thì win
  * Có nhiều map cho người chơi lựa chọn với các loại quái và boss khác nhau
  * Trò chơi sẽ kết thúc khi phi thuyền của Slime hết máu hoặc tiêu diệt được boss
   
## 4. Một vài hình ảnh trong game

## 5. Về source code của game
- Folder src: lưu file main và các thành phần cơ bản được tái sử dụng nhiều trong game 
  * main: file chạy chương trình
  * Function: chứa các hàm cần thiết
    + BasicFn: chứa các hàm khởi tạo SDL cơ bản, các biến cơ bản, hàm nhập, xuất data
    + Func: chứa các hàm tính toán phức tạp
  * Object: chứa các đối tượng được cơ bản
    + BigObj: đối tượng có thể hiển thị lên màn hình
    + Button: đối tượng có thể bấm
    + MovingObj: đối tượng có thể di chuyển trên màn hình
    + Screen: đối tượng chứa hình ảnh màn hình
    + TextObj: đối tượng có thể viết lên màn hình
  * TimeManage: bộ điều khiển, xử lý thời gian trong quá trình chơi game
- Folder menu: lưu màn hình bắt đầu của game, điều hướng các hoạt động trước khi gameplay.
- Folder gameplay: lưu toàn bộ hoạt động trong lúc chơi game
  * Game: điều khiển, xử lý game
  * Player: xử lý thao tác, hình ảnh của người chơi
  * Opponent: điều khiển các thành phần không phải người chơi
    + Enemy: thành phần kẻ địch, xử lý các thao tác đuổi, va chạm 
    + Boss: thành phần kẻ địch boss, xử lý nhiều thao tác đuổi, va chạm, dùng kĩ năng
    + Exp: thành phần rơi ra từ Enemy
    + Wave: điều khiển, xử lý các đợt kẻ địch, tỉ lệ xuất hiện các loại kẻ địch
  * Power: các loại kĩ năng của player
    + Orb: quản lý skill orb
    + FireBall: quản lý skill fireball
    + Zone: quản lý skill zone
    + Kameha: quản lý skill kameha
  * LevelUp: quản lý việc tăng cấp, nâng cấp các kĩ năng
    + Card: quản lý các lựa chọn lúc tăng cấp
    + Power up: xử lý việc nâng câp các loại kĩ năng
    * DMG: quản lý hiện thị sát thương gây ra 
    * Detail: xử lý KillCount và TimeCount
- Folder asset: Chứa các hình ảnh, âm thanh, phông chữ load trong gameplay
