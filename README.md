# TimePresenter（时间悬浮窗）
## 功能
- 在屏幕上置顶显示时间；
- 开机自启；
- 保存配置，以便下次使用。
## 运行环境
- 系统要求：Windows Vista 或更高版本；
- 权限要求：读写注册表 HKEY_CURRENT_USER\Software。
## 使用方法
### 启动程序
&emsp;&emsp;本程序启动时会检测计算机上是否已有本程序的一个进程正在运行，若未检测到正在运行的进程，则正常启动本程序，否则，本程序将发送消息，使正在运行的进程打开“设置”窗口，然后关闭本程序。  
&emsp;&emsp;程序启动后，将检查配置信息，若配置信息为空或存在错误，配置信息将被重置为默认值。  
&emsp;&emsp;待各项初始化任务完成后，程序主窗口（如下图）将会置顶显示，主窗口具有透明背景，用户无法点击到本窗口，默认位置为主显示器右上角。  
![image](https://github.com/MCjiaozi/TimePresenter/assets/64739528/207542f1-8864-481d-a304-821a8c58e2bd)  
&emsp;&emsp;程序启动后，在托盘栏可见程序图标，左键、中键或右键单击图标后将显示菜单（如下图）。  
![image](https://github.com/MCjiaozi/TimePresenter/assets/64739528/93fc861f-864e-445d-9b7b-2c720e9a6a34)![image](https://github.com/MCjiaozi/TimePresenter/assets/64739528/479d1856-f6ee-4eb7-b914-3a5b81600ec9)
### 程序设置
&emsp;&emsp;单击程序托盘栏图标，显示菜单后单击“设置”，即可打开设置窗口（如下图）。  
![image](https://github.com/MCjiaozi/TimePresenter/assets/64739528/96562ecb-b646-4972-8de2-0c2b0beaa416)
#### 开机时自动启动
&emsp;&emsp;勾选此项后，程序会被添加至系统开机自启项中，用户登录后，程序将会自动启动。请注意：若程序路径或名称被改变，设置的开机自启将失效，重新勾选此项后功能方可恢复正常。
#### 格式
&emsp;&emsp;本设置项影响主窗口文字内容，可根据用户喜好修改格式，键入的指定字符串将被替换为对应内容，对应关系如下：
| 符号 | YY | mm | dd | HH | MM | SS | \n |
| :-----| :----- | :----- | :----- | :----- | :----- | :----- | :----- |
| 内容 | 年 | 月 | 日 | 时 | 分 | 秒 | 换行 |  

&emsp;&emsp;例如：YY/mm/dd 将被替换为 2023/03/05，HH:MM:SS 将被替换为 16:03:30。（以实际时间为准）。下拉列表中已有预设格式和配置信息中保存的格式（如图） 。 
![image](https://github.com/MCjiaozi/TimePresenter/assets/64739528/35d4bd90-a666-4b27-884c-a90b71a118a1)
#### 样式
&emsp;&emsp;本设置项影响主窗口文字样式，可修改字号、字色、字体，其中字体编辑框的下拉列表中已列举系统内的所有字体和配置信息中保存的字体（如图）。  
![image](https://github.com/MCjiaozi/TimePresenter/assets/64739528/d4bd27ad-9cf5-4e45-841d-a8effd60c7ac)
#### 位置
&emsp;&emsp;本设置影响主窗口位置。位置的定位类似平面直角坐标系，X轴正方向为正右，Y轴正方向为正下。坐标原点可修改为右上（默认）、左上、中上、左中、中央、右中、左下、中下、右下。偏移坐标为相对原点的相对坐标。单位为像素。
#### 高级
&emsp;&emsp;清除所有数据并退出：删除程序在注册表中存储的数据，然后退出程序。
&emsp;&emsp;恢复默认设置：删除程序在注册表中存储的数据，然后重新初始化程序。
### 退出程序
&emsp;&emsp;单击程序托盘栏图标，显示菜单后单击“退出”，即可退出程序。或在设置中单击“清除所有数据并退出”以清除本程序存储的所有数据然后退出。
## 数据存储
&emsp;&emsp;本程序将配置信息存储在注册表中。具体路径为：  
计算机\HKEY_CURRENT_USER\Software\TimePresenter\TimePresenter\Settings  
各值项含义如下：
| 名称 | FontFamily | FontSize | Format | Position | RGB | ShiftX | ShiftY |
| :-----| :----- | :----- | :----- | :----- | :----- | :----- | :----- |
| 含义 | 字体 | 字号 | 格式 | 位置 | 字体颜色 | 坐标 X | 坐标 Y |  

&emsp;&emsp;开机自启项存储在：
计算机\HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
值项名称为 TimePresenter，数据为程序路径。
## 下载已编译的可执行程序
- [GitHub](https://github.com/MCjiaozi/TimePresenter/releases)
- [发布网站](https://www.mcjiaozi.com/TimePresenter/)
