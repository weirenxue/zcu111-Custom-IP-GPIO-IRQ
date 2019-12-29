# ZCU111 自訂一個IP，用以接收外部訊號源，觸發輸出IRQ訊號。
##### 開發工具：Vivado2019.1，SDK2019.1，ZCU111開發板與相關資料。

#### 1. IP功能與I/O描述：
    1. 主要功能：以外部訊號當作時脈，抓取其正緣，並輸出訊號告知CPU已正緣觸發，若CPU處理完畢，
        將告知IP已處理過，並由IP自己把IRQ訊號設為低準位，詳細步驟參考流程圖。
    2. I/O
        1. 輸入
            1. CLK_LF(Clock Low Frequency)：用來接外部的時脈，其頻率較CPU的時脈低。
        2. 輸出
            1. IRQ(Interrupt ReQuest)：中斷請求訊號。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/Flow_Chart.png"  title="Flow Chart" width="25%"></p>

#### 2. 開啟Vivado專案，主選單Tool/Create and Package New IP。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/Create_and_Package_New_IP.png"  title="Create and Package New IP.png" width="20%"></p>

#### 3. Next>到下一頁，選取Create a new AXI4 peripheral，再Next>到下一頁填寫IP相關資訊(名字、版本等等)。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/Create_a_new_AXI4_peripheral.png"  title="Create a new AXI4 peripheral" width="50%"></p>

#### 4. Next>到下一頁，設定好暫存器數量後繼續往下，選擇Edit IP然後Finish。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/Edit_IP.png"  title="Edit IP" width="60%"></p>

#### 5. 此時會自動開啟一個新的Vivado視窗，這是IP的專案，在Design Sources中會看到兩個.v檔(.v for verilog and .vhd for VHDL)，檔名是根據IP名稱取的，因此可能略有不同。
    1. GPIO_irq_v1_0(GPIO_irq_v1_0.v)：
		包裝IP的hdl，只添加或刪除I/O。
    2. GPIO_irq_v1_0_S00_AXI_inst:GPIO_irq_v1_0_S00_AXI(GPIO_irq_v1_0_S00_AXI.v)：
		IP本體，要添加或刪除功能都在此檔案內。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/IP_verilog.png"  title="IP verilog" width="50%"></p>


#### 6. 先修改GPIO_irq_v1_0_S00_AXI.v，並存檔。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/Inst_verilog.png"  title="Instance verilog" width="50%"></p>

#### 7. 再修改GPIO_irq_v1_0.v，存檔後確定沒有語法錯誤的提示。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/Wrapper_verilog.png"  title="Wrapper verilog" width="50%"></p>

#### 8. 回到Package IP頁面中的Port and Interfaces，點擊上排藍字，自動合併改變。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/Merge_Changes_From_Ports_and_Interfaces_Wizard.png"  title="Merge Changes From Ports and Interfaces Wizard" width="60%"></p>

#### 9. irq上按滑鼠右鍵，Edit Interface，將SENSITIVITY的值改成EDGE_RISING。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/IRQ_Edit_Interface.png"  title="IRQ Edit Interface" width="60%"></p>

#### 10. clk_lf上按滑鼠右鍵，Auto Infer Single Bit Interface/Data。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/Auto_Infer_Single_Bit_Interface_Data.png"  title="Auto Infer Single Bit Interface Data" width="60%"></p>

#### 11. 換到File Groups頁面，一樣自動合併改變，確定都打綠色勾之後，切換到Review and Package，Re-Package IP重新打包IP，只要IP有更動都需要這些步驟。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/File_Group_Merge_Change_and_Re_Package_IP.png"  title="File Group Merge Change and Re Package IP" width="60%"></p>

#### 12. 會出現要不要關閉此IP專案，通常在開發階段我是不會關的，如果還要改的話就直接改，不需要重新開啟。
<p align=center><img src="https://github.com/weirenxue/zcu111-Custom-IP-GPIO-IRQ/blob/feature-create-custom-ip/pic/Close_Project_or_not.png"  title="Close Project or not" width="20%"></p>
