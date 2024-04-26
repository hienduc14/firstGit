# Survivor (I AM SLIME)
- Cấu trúc code và thử nghiệm game: https://youtu.be/78Md1xfbBT4?si=YcQX4fa0P1tJah_j

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
  - **Bước 1:** Đầu tiên, Cài codeblocks-20.03mingw và những thứ cần thiết để chạy được SDL2 trên CodeBlocks, bao gồm SDL2, SDL_Image, SDL_Mixer, SDL_TTF

    Tham khảo tại [lazyfoo.net](https://lazyfoo.net/tutorials/SDL/index.php)
    
  - **Bước 2:** Tải file Game:
      * Nếu CodeBlocks 32 bit:
         + Chọn Code -> Rồi Download File Zip của repo này về
      * Nếu CodeBlocks 64 bit:
         + Tải file rar (đầu tiên) từ release này về [https://github.com/hienduc14/firstGit/releases/tag/download)
     
  - **Bước 3:** Click vào file Survivor.exe để chơi

## 1. Bắt đầu game

- Màn hình chính:

![image](https://github.com/hienduc14/firstGit/blob/master/menu/Menu.png)

- Click vào nút "Play" để chọn map. Có 3 map:
  * Meadow: Thảo nguyên 
  * Graveyard: Nghĩa địa
  * Volcano: Núi lửa
![image](https://github.com/hienduc14/firstGit/assets/160812390/71f1d341-a6e7-4214-98d0-9e49f3ae113b)

- Chọn "Options" ![image](https://github.com/hienduc14/firstGit/assets/160812390/26171803-8402-435f-aa6f-004174166e37)
trên góc trên phải để cài đặt âm thanh và hiển thị sát thương
  * Âm thanh: có thể bật, tắt âm thanh, thay đổi độ lớn của nhạc nền(Music) và âm thanh hiệu ứng(Sound Effect)
  * DMG Numbers: Tắt/Bật hiển thị số sát thương gây ra
  * Exit: để thoát game.
![image](https://github.com/hienduc14/firstGit/assets/160812390/a7182a33-b4ad-46b5-890c-7a48dfe3f686)

- Chọn "Tutorial" để xem hướng dẫn các phím điều khiển
![image](https://github.com/hienduc14/firstGit/assets/160812390/8c0ab9a0-4855-450e-81d0-e21866d79368)

- Chọn "Shop" để mua các trang phục bằng tiền kiếm được trong game
![image](https://github.com/hienduc14/firstGit/assets/160812390/1dafef2c-1003-4149-bc81-d6ecd4416446)

## 2. Các thành phần trong game
### a. Người chơi
- Slime: ![image](https://github.com/hienduc14/firstGit/assets/160812390/3bdf0741-ecee-43f0-ba33-fe2a118d4896)
 là bọng nhớt do người chơi điều khiển, bị trừ máu nếu va chạm với kẻ địch hoặc kĩ năng của kẻ địch.
- Các loại kĩ năng chủ động:
  *  Jump :![image](https://github.com/hienduc14/firstGit/assets/160812390/a30a4522-7560-4088-b606-2759a1afed66)
  Có thể nhảy qua quái và đạn, có thời gian hồi chiêu 3s.
  *  Kameha :![image](https://github.com/hienduc14/firstGit/assets/160812390/8deed4d0-e810-40de-a550-5db1092590bb)
 nhấn giữ L để vận công và nhả L để bắn chưởng. Khi vẫn công sẽ đứng im, có thể điều chỉnh góc bắn bằng W S, có thể huỷ trong lúc vận bằng nhấn giữ núi O. Khi bắn chưởng, hi sinh 1/2 máu và đứng im.
- Các loại kĩ năng tự động:
  *  Orb : ![image](https://github.com/hienduc14/firstGit/assets/160812390/e90b36e4-df07-4130-b66b-28f269a7315c)
đạn bắn theo hướng di chuyển
  *  FireBall :![image](https://github.com/hienduc14/firstGit/assets/160812390/c9f505a8-5482-4c5b-9b1b-a173c54f08dc)
 đạn tự nhắm vào kẻ thù gần nhất
  *  Zone :![image](https://github.com/hienduc14/firstGit/assets/160812390/50b942eb-6edc-42ee-b2ab-2ef8667b70c1)
 toạ ra 1 vùng gây sát thương xung quanh slime

- Tăng cấp :![image](https://github.com/hienduc14/firstGit/assets/160812390/5ff1cc88-1455-43c0-bdb5-417b26b171b0)
 khi nhặt đủ kinh nghiệm để lên cấp sẽ được chọn 1 trong 3 nâng cấp: nâng cấp kĩ năng tự động hoặc tăng chỉ số cá nhân

- Thông tin của Slime: 
  * Thanh máu:![image](https://github.com/hienduc14/firstGit/assets/160812390/01cfc0cf-a0b4-44bb-9c03-d5d59b9e451f)
 cho biết slime còn lại bao nhiêu phần máu
  * Thanh kinh nghiệm:![image](https://github.com/hienduc14/firstGit/assets/160812390/11fd01a2-570e-4dc9-8b9c-e1f65fd17ac6)
 cho biết slime cần tích thêm bao nhiêu phần kinh nghiệm để tăng cấp
### b. Kẻ địch
- Quái nhỏ:
![image](https://github.com/hienduc14/firstGit/assets/160812390/eac06f69-4b0c-408b-aa1a-4adb515573a3)
![image](https://github.com/hienduc14/firstGit/assets/160812390/e6c620ea-4fac-4c9c-ab01-c4c6affe0160)
![image](https://github.com/hienduc14/firstGit/assets/160812390/08e6a316-fce5-45a2-aea0-95e4d3b636fb)

  đa dạng quái nhỏ đến từ các hướng đuổi theo Slime, khiến Slime mất máu khi chạm vào Slime. Khi giết có tỉ lệ rơi DropItem
- Dropitem : các vật phẩm rơi ra khi giết quái nhỏ có thể hấp thụ
  * Exp: ![image](https://github.com/hienduc14/firstGit/assets/160812390/aa0fdf96-2298-41fe-8b36-dc263e435676)
giúp Slime tăng cấp
  * Heart: ![image](https://github.com/hienduc14/firstGit/assets/160812390/303bb3af-c050-4350-b8ec-2b3535d6ceb0)
giúp Slime hồi máu
  * Coin:![image](https://github.com/hienduc14/firstGit/assets/160812390/a0db8d5b-1bfa-4a97-8a5d-ac3134f271c1)
 có thể dùng để mua hàng trong shop
- Slime lớn (Boss) :![image](https://github.com/hienduc14/firstGit/assets/160812390/70eef403-b693-46e9-ace4-5a35a2c3308d)
 Slime loại boss cỡ lớn, lượng máu cao xuất hiện sau một thời gian ở map Meadow. Có kĩ năng nhắm vào người chơi và nhảy đến
- Ghost lớn (Boss) :![image](https://github.com/hienduc14/firstGit/assets/160812390/e8af1854-9f4f-4864-b174-8e165ec9b812)
 Ghost loại boss có lượng máu cao, có thể tàng hình và triệu hồi các ghost nhỏ từ tất cả các hướng đuổi Slime
- FlameBoss (Boss) :![image](https://github.com/hienduc14/firstGit/assets/160812390/d19a91da-81f1-43b3-b7bb-7db19a1747b3)
 Người lửa loại boss có lượng máu cao, có khả năng vận công và bắn chưởng lửa
- Thanh máu :![image](https://github.com/hienduc14/firstGit/assets/160812390/fa974336-b2ac-430d-b00c-138125c7b460)
 Thanh máu của kẻ địch, hiện khi đối đầu với boss
### c. Khác
- KillCount:![image](https://github.com/hienduc14/firstGit/assets/160812390/1550e451-82c3-4e46-943e-7896bd1242a3)
 đếm đã giết được bao nhiêu quái
- TimeCount:![image](https://github.com/hienduc14/firstGit/assets/160812390/5e552a86-93d1-431e-99e1-722487e2524c)
 đếm đã sinh tồn được bao lâu
- Nút tạm dừng (pause) :![image](https://github.com/hienduc14/firstGit/assets/160812390/86bb21f6-e83a-4d2a-8ba4-5d99ffafa592)
 Click nút này sẽ tạm dừng trò chơi. Sau khi nhấn, hiện lên màn hình chờ như hình dưới, bao gồm các lựa chọn:
  * Tiếp tục trò chơi
  * Quay về màn hình chính
  * Điều chỉnh âm thanh
  * Tắt/Bật hiển thị sát thương
  ![image](https://github.com/hienduc14/firstGit/assets/160812390/af88daef-40de-48d9-b2dc-ece0782a3f1a)


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
![image](https://github.com/hienduc14/firstGit/assets/160812390/05cc89d1-9b01-4389-b365-db03545e55a3)
![image](https://github.com/hienduc14/firstGit/assets/160812390/59867f99-3854-4b79-bb8a-bb9355d90ffc)
![image](https://github.com/hienduc14/firstGit/assets/160812390/d8643909-0bd6-43dc-ac3d-fb1d40fd76d3)
![image](https://github.com/hienduc14/firstGit/assets/160812390/8e76b400-7aa3-42b9-848b-6062923c5244)
![image](https://github.com/hienduc14/firstGit/assets/160812390/ac4dc339-87d9-48d7-82d8-7c293308fe73)

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
- Folder menu: lưu màn hình bắt đầu của game, điều hướng các hoạt động trước khi gameplay, chọn map

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
