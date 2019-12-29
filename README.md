# ZCU111 自訂一個IP，用以接收外部訊號源，觸發輸出IRQ訊號。
##### 開發工具：Vivado2019.1，SDK2019.1，ZCU111開發板與相關資料。

#### 1. IP功能與I/O描述：
    1. 主要功能：以外部訊號當作時脈，抓取其正緣，並輸出訊號告知CPU已正緣觸發。
    2. I/O
        1. 輸入
            1. CLK_LF(Clock Low Frequency)：用來接外部的時脈，其頻率較CPU的時脈低。
        2. 輸出
            1. IRQ(Interrupt ReQuest)：中斷請求訊號。
Flow_Chart.png
#### 2. 開啟Vivado專案，主選單Tool/Create and Package New IP。
Create_and_Package_New_IP.png


#### 3. Next>到下一頁，選取Create a new AXI4 peripheral，再Next>到下一頁填寫IP相關資訊(名字、版本等等)。
Create_a_new_AXI4_peripheral.png

#### 4. Next>到下一頁，設定好暫存器數量後繼續往下，選擇Edit IP然後Finish。
Edit_IP.png

#### 5. 此時會自動開啟一個新的Vivado視窗，這是IP的專案，在Design Sources中會看到兩個.v檔(.v for verilog and .vhd for VHDL)，檔名是根據IP名稱取的，因此可能略有不同。
    1. myip_v1_0(myip_v1_0.v)：包裝IP的.v檔，只添加或刪除I/O。
    2. myip_v1_0_S00_AXI_inst:myip_V1_0_S00_AXI：IP本體，要添加或刪除功能都在此檔案內。
IP_verilog.png

#### 6. 先修改myip_v1_0_S00_AXI_inst:myip_V1_0_S00_AXI，並存檔。
IP_verilog.png

#### 7. 再修改myip_v1_0(myip_v1_0.v)，存檔後確定沒有語法錯誤的提示。
Wrapper_verilog.png

#### 8. 回到Package IP頁面中的Port and Interfaces，點擊上排藍字，自動合併改變。
Merge_Changes_From_Ports_and_Interfaces_Wizard.png

#### 9. irq上按滑鼠右鍵，Edit Interface，將SENSITIVITY的值改成EDGE_RISING。
IRQ_Edit_Interface.png

#### 10. clk_lf上按滑鼠右鍵，Auto Infer Single Bit Interface/Data。
Auto_Infer_Single_Bit_Interface_Data.png

#### 11. 換到File Groups頁面，一樣自動合併改變，確定都打綠色勾之後，切換到Review and Package，Re-Package IP重新打包IP，只要IP有更動都需要這些步驟。
File_Group_Merge_Change_and_Re_Package_IP.png

#### 12. 會出現要不要關閉此IP專案，通常在開發階段我是不會關的，如果還要改的話就直接改，不需要重新開啟。
Close_Project_or_not