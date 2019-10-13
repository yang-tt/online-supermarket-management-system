#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define U 200 //商品数量上限
#define S 100 //店铺数量上限
#define P 100 //顾客数量上限
#define O 100 //订单数量上限


/*储存变量的结构体*/
struct product //商品信息
{
    char product_ID [7];//商品ID
    char product_market [2];//商品所属超市
    char product_name [81];//商品名称
    float price_cost;//商品进价
    float price_selling;//商品售价
    int sales;//商品销量
    int storage;//商品库存
    float price_discount;//折扣价格
    int discount_start_year;//折扣开始年
    int discount_start_month;//折扣开始月
    int discount_start_date;//折扣开始日
    int discount_start_hour;//折扣开始时
    int discount_start_min;//折扣开始分
    int discount_end_year;//折扣结束年
    int discount_end_month;//折扣结束月
    int discount_end_date;//折扣结束日
    int discount_end_hour;//折扣结束时
    int discount_end_min;//折扣结束分
    char season[81];//季节判断
} product[U],temp_product[U];

struct userType /*顾客信息*/
{
    char userID[81];    /*顾客id*/
    char userCode[81];  /*顾客密码*/
    char userName[81];  /*顾客姓名*/
    char userSex[81];   /*顾客性别*/
    char userPhone[81]; /*顾客电话*/
    char userMail[81];  /*顾客邮箱*/
    char userAddress[81];   /*顾客地址*/
    float userBalance;   /*顾客余额*/
}user[100];

struct adminType    /*管理员信息*/
{
    char adminID[81];
    char adminCode[81];
    char adminName[81];
    char adminMarket[81];
    char adminMail[81];
}admin[20];

struct TIME
{
    int year;//当前年
    int month;//当前月
    int date;//当前日
    int hour;//当前时
    int min;//当前分
}tt;

struct customer_unfinished_order/*顾客未完成订单信息*/
{
    char o_id[81];//订单编号
    char o_time[20];//订单时间
    char g_id[10];//商品编号
    char g_name[81];//商品名称
    int  g_number;//商品数量
    float g_price;//商品单价
    float g_total;//商品总价
    float g_all;//合计
    char  g_s_id[81];//商品所属超市名称
    char season[81];//季节判断
}cus_unorder[U];

struct customer_finished_order/*顾客已完成订单信息*/
{
    char o_id[81];//订单编号
    char o_time[20];//订单时间
    char g_id[10];//商品编号
    char g_name[81];//商品名称
    int  g_number;//商品数量
    float g_price;//商品单价
    float g_total;//商品总价
    float g_all;//合计
    int   g_sales;//商品销量
    float g_benefit;//商品利润
    char  g_s_id[81];//商品所属超市名称
    char season[81];//季节判断
}cus_order[U];

struct store_unfinished_order/*顾客未完成订单信息*/
{
    char o_id[81];//订单编号
    char o_time[20];//订单时间
    char g_id[10];//商品编号
    char g_name[81];//商品名称
    int  g_number;//商品数量
    float g_price;//商品单价
    float g_total;//商品总价
    float g_all;//合计
    int  g_s_id;//商品所属超市编号
}sto_unorder[P];

struct store_finished_order/*顾客已完成订单信息*/
{
    char o_id[81];//订单编号
    char o_time[20];//订单时间
    char g_id[10];//商品编号
    char g_name[81];//商品名称
    int  g_number;//商品数量
    float g_price;//商品单价
    float g_total;//商品总价
    float g_all;//合计
    int  g_sales;//商品销量
    float g_benefit;//商品销量
    int  g_s_id;//商品所属超市编号
}sto_order[P];

/*全局变量声明部分*/
int user_num;   //全局变量，用来计入用户总数
int admin_num;  //全局变量，用来计入管理员总数
int product_num;//全局变量，用来计入商品总数

/*函数声明部分*/
void primary_menu();//主菜单界面
void read_user();//读取用户信息
void read_product();//读取文件中商品信息
//void read_unorder();//读取用户购物车信息
//void read_order();//读取用户订单信息
//void user_func();//用户功能界面
void store_menu();  //商品菜单函数
void user_menu();  //用户菜单函数
void user_search_name();//用户根据商品名称搜索
void user_search_market();//用户根据超市名称搜索
void user_show_discount();//用户展示折扣商品
void user_show_all();//用户展示所有商品
//void ord_price();//根据价格排序
//void ord_sales();//根据销量排序
void ord_discount();//筛选折扣商品
void user_payment();//用户购买商品
void user_buy(int serial_number);
void admin_product_show(int serial_number);
void ord_price_raise_search(int serial_number);
void ord_sales_search(int serial_number);
//设一个serial_number做参量，用这个参量去定位用户信息
void read_admin();
void user_information();    //用户个人信息菜单
void user_change_phone(int serial_number);    //用户修改电话
void user_change_code(int serial_number); //用户修改密码
void user_change_mail(int serial_number); //用户修改邮箱
void user_change_address(int serial_number);  //用户修改地址
int isEmail(char *email);    //邮箱容错
void admin_menu();
void admin_change_email(int serial_number);
void admin_view_order(int serial_number);
void s_sales_ord();
void s_profit_ord(int serial_number);
void s_turnover_ord(int serial_number);
void adimin_judge_sales();
void customer_unfinished_order();   //用户查看购物车函数
void customer_finished_order(); //用户查看订单函数
void admin_manage_order();  //管理员订单管理总函数
void admin_view_order();    //管理员查看订单情况函数
void products_menu();   //商品界面函数
void goodord_sale();    //按销量和营业额对订单商品排序函数
void goodord_price();   //查看输出利润最高和最低的商品函数
void admin_menu();  //管理员菜单函数
void hotSale(int serial_number);    //附加选项，根据季节判断商品


/*函数定义部分*/
void primary_menu()//主菜单界面
{
    int option = 0; /*开关*/
    int serial_number;
    while(option != 4)  /*菜单*/
    {
        printf("请选择您的用户类型： \n 1)顾客\n 2)管理员\n 3)游客\n 4)退出程序\n");
        scanf("%d", &option);
        while(option!=1&&option!=2&&option!=3&&option!=4)
        {
            printf("您的输入有误，请重新输入您的选择： \n");
            fflush(stdin);
            scanf("%d", &option);
        }
        switch(option)
        {
            case 1:
                system("cls");
                serial_number = user_login();   /*用户登录*/
                user_menu(serial_number);    /*用户菜单*/
                break;
            case 2:
                system("cls");
                serial_number = admin_login();  /*管理员登录*/
                admin_menu(serial_number);   /*管理员菜单*/
                break;
            case 3:
                store_menu(-1);
                printf("\n浏览结束，请登录以进行更多操作。\n");
                break;
            case 4:
                exit(0);
        }
    }
    
}


void store_menu(int serial_number)/*商品功能界面*/
{
    int choice;
    int i=0;
    while(i==0)
    {
        system("cls");
        printf("请输入你想要进行搜索的类别\n1.按照商品名称搜索\n2.按照超市名称搜索\n3.显示折扣中的商品\n4.展示全部商品\n5.根据价格排序所有商品\n6.根据销量排序所有商品\n7.当季热销商品推荐\n8.返回上一级菜单\n9.退出\n请输入你的选择：\n");
        scanf("%d",&choice);
        fflush(stdin);
        
        while(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7&&choice!=8&&choice!=9)
        {
            printf("您的输入有误，请重新输入:\n");
            scanf("%d", &choice);
            fflush(stdin);
        }
        
        switch(choice)
        {
            case 1:
                user_search_name(serial_number);    //按商品名称查询
                break;
            case 2:
                user_search_market(serial_number);  //按超市名称查询
                break;
            case 3:
                user_show_discount(serial_number);  //按是否有折扣信息过滤查询结果
                break;
            case 4:
                user_show_all(serial_number);   //展示所有商品
                break;
            case 5:
                ord_price_raise_search(serial_number);  //按价格排序
                break;
            case 6:
                ord_sales_search(serial_number);    //按销量排序
                break;
            case 7:
                hotSale(serial_number);     //热销商品推荐
                break;
            case 8:
                user_menu(serial_number);   //返回用户菜单
                break;
            case 9:
                exit(1);
                
        }
        
    }
}


void customer_unfinished_order(int serial_number)   //用户查看购物车函数
{
    int i=0,m=0,n=0,choice = 0,a=0,b;
    int decide = 0;
    char filename[100],name[]="购物车.txt";
    FILE *customer_unfinished_orderFile;
    read_user();//读取用户信息
    b = serial_number;
    strcpy(filename,user[serial_number].userID);
    strcat(filename,name);
    customer_unfinished_orderFile=fopen(filename,"r");
    
    printf("您的购物车记录如下：\n");
    
    if(customer_unfinished_orderFile==NULL) //检查
    {
        printf("对不起，您尚无购物车记录\n");
        while(m==0)
        {
            printf("是否需要继续购物？\n1. 是\n2. 否\n");
            scanf("%d", &decide);
            switch(decide)
            {
                case 1:
                    store_menu(serial_number);  //用户功能界面函数
                    break;
                case 2:
                    exit(0);
                default:
                    printf("对不起，您的输入有误！\n");
                    continue;
            }
            m=1;
        }
    }
    while(!feof(customer_unfinished_orderFile))
    {
        fscanf(customer_unfinished_orderFile,"%s %s %s %s %s %d %f %f\n",
               cus_unorder[a].o_id,
               cus_unorder[a].o_time,
               cus_unorder[a].g_s_id,
               cus_unorder[a].g_id,
               cus_unorder[a].g_name,
               &cus_unorder[a].g_number,
               &cus_unorder[a].g_price,
               &cus_unorder[a].g_total
               );
        a++;
    }   //读取用户购物车信息
    fclose(customer_unfinished_orderFile);
    printf(" 订单编号  订单时间  商品编号  商品名称  商品数量  商品单价  商品总价   商品所属超市编号  \n");
    for(i=0;i<a;i++)
        printf("%7s %7s %7s %7s %7s %7d %7.2f %7.2f\n",
               cus_unorder[i].o_id,
               cus_unorder[i].o_time,
               cus_unorder[i].g_s_id,
               cus_unorder[i].g_id,
               cus_unorder[i].g_name,
               cus_unorder[i].g_number,
               cus_unorder[i].g_price,
               cus_unorder[i].g_total
               );
    
    
    while(n==0)
    {
        printf("请选择下一步的操作：\n1.结算\n2.继续购物\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                user_payment(serial_number);    //付款界面函数
                break;
            case 2:
                store_menu(serial_number);  //商品界面函数
                break;
            default:
                printf("对不起，您的输入有误！\n");
                continue;
        }
        n=1;
    }
}


void customer_finished_order(int serial_number) //用户查看订单函数
{
    int i=0,m=0,n=0,a=0,b;
    int decide,choice;
    char filename[100],name[]="订单.txt";
    FILE *customer_finished_orderFile;
    read_user();//读取用户信息
    b = serial_number;
    strcpy(filename,user[b].userID);
    strcat(filename,name);
    customer_finished_orderFile=fopen(filename,"r");
    if(customer_finished_orderFile==NULL)//检查
    {
        printf("对不起，您还没有订单记录。\n");
        while(m==0)
        {
            printf("是否需要继续购物？\n1. 是\n2. 否\n");
            scanf("%d", &choice);
            switch(choice)
            {
                case 1:
                    store_menu(serial_number);  //用户功能界面函数
                    break;
                case 2:
                    exit(0);
                default:
                    continue;
            }
            m=1;
        }
    }
    
    while(!feof(customer_finished_orderFile))
    {
        fscanf(customer_finished_orderFile,"%s %s %s %s %s %d %f %f\n",
               cus_unorder[a].o_id,
               cus_unorder[a].o_time,
               cus_unorder[a].g_s_id,
               cus_unorder[a].g_id,
               cus_unorder[a].g_name,
               &cus_unorder[a].g_number,
               &cus_unorder[a].g_price,
               &cus_unorder[a].g_total
               );
        a++;
    }   //读取用户订单信息
    
    printf(" 订单编号  订单时间  商品编号  商品名称  商品数量  商品单价  商品总价   商品所属超市编号  \n");
    for(i=0;i<a;i++)
        printf("%7s %7s %7s %7s %7s %7d %7.2f %7.2f\n",
               cus_unorder[i].o_id,
               cus_unorder[i].o_time,
               cus_unorder[i].g_s_id,
               cus_unorder[i].g_id,
               cus_unorder[i].g_name,
               cus_unorder[i].g_number,
               cus_unorder[i].g_price,
               cus_unorder[i].g_total
               );
    fclose(customer_finished_orderFile);
    
    while(n==0)
    {
        printf("是否继续购物？\n1. 是\n2. 否\n");
        scanf("%d", &decide);
        switch(decide)
        {
            case 1:
                store_menu(serial_number);  //用户功能界面函数
                break;
            case 2:
                exit(0);
            default:
                printf("对不起，您的输入有误！\n");
                continue;
        }
        n=1;
    }
}



void user_search_name(int serial_number)    //用户根据商品名称搜索
{
    read_product();//读取商品信息
    int i,j,k;
    i=0,k=0,j=0;
    char pro_name[20];
    FILE *infile_rank;
    infile_rank = fopen("Ranking.txt","w");
    while(k==0)
    {
        printf("\n========================\n");
        printf("请输入您要查询的商品名称(输入return返回上一级菜单):\n");
        scanf("%s",pro_name);
        fflush(stdin);
        for(i=0;i<product_num;i++)
        {
            if(strcmp(pro_name,product[i].product_name)==0)
            {
                k=1;
                j++;    //商品在本页的序号
                printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n",
                       j,
                       product[i].product_ID,
                       product[i].product_name,
                       product[i].product_market,
                       product[i].price_selling,
                       product[i].storage);
                
                /*将搜索出的结果写入一个新的文件，以便后续排序使用*/
                fprintf(infile_rank,"%s\t %s\t %s\t %.2f\t %.2f\t %d\t %d\t %.2f\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
                        product[i].product_ID,
                        product[i].product_market,
                        product[i].product_name,
                        product[i].price_cost,
                        product[i].price_selling,
                        product[i].sales,
                        product[i].storage,
                        product[i].price_discount,
                        product[i].discount_start_year,
                        product[i].discount_start_month,
                        product[i].discount_start_date,
                        product[i].discount_start_hour,
                        product[i].discount_start_min,
                        product[i].discount_end_year,
                        product[i].discount_end_month,
                        product[i].discount_end_date,
                        product[i].discount_end_hour,
                        product[i].discount_end_min);
            }
            else if(strcmp(pro_name,"return")==0)
                store_menu(serial_number);  //返回用户功能界面函数
            
        }
        fclose(infile_rank);
        
        if(k==1)
        {
            printf("\n请输入您需要的操作序号：\n1.筛选折扣商品\n2.购买商品\n3.返回上一级菜单\n4.退出\n");
            int option;
            scanf("%d",&option);
            while(option!=1&&option!=2&&option!=3&&option!=4&&option!=5&&option!=6)
            {
                printf("您的输入有误，请重新输入");
                scanf("%d",&option);
            }
            
            switch (option)
            {
                    
                case 1:
                    ord_discount(serial_number);    //筛选折扣商品
                    break;
                case 2:
                    if(serial_number != -1)
                        user_buy(serial_number);    //加购物车
                    user_payment(serial_number);    //付款
                    break;
                case 3:
                    store_menu(serial_number);  //用户功能界面
                    break;
                case 4:
                    exit(1);
                    
            }
        }
        if(k==0)
            printf("您输入的商品名称不存在，请重新输入:");
    }
}


void user_search_market(int serial_number)  //用户根据超市名称搜索
{
    read_product(); //读取商品信息
    int i,j,k;
    i=0,k=0,j=0;
    char mkt_name[20];
    FILE *infile_rank;
    infile_rank = fopen("Ranking.txt","w");
    while(k==0)
    {
        printf("\n========================\n");
        printf("请输入您要查询的超市名称(输入return返回上一级菜单):\n");
        scanf("%s",mkt_name);
        fflush(stdin);
        for(i=0;i<product_num;i++)
        {
            if(strcmp(mkt_name,product[i].product_market)==0)
            {
                k=1;
                j++;//商品在本页的编号
                printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n",
                       j,
                       product[i].product_ID,
                       product[i].product_name,
                       product[i].product_market,
                       product[i].price_selling,
                       product[i].storage);
                
                /*将搜索出的结果写入一个新的文件，以便后续排序使用*/
                fprintf(infile_rank,"%s\t %s\t %s\t %.2f\t %.2f\t %d\t %d\t %.2f\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
                        product[i].product_ID,
                        product[i].product_market,
                        product[i].product_name,
                        product[i].price_cost,
                        product[i].price_selling,
                        product[i].sales,
                        product[i].storage,
                        product[i].price_discount,
                        product[i].discount_start_year,
                        product[i].discount_start_month,
                        product[i].discount_start_date,
                        product[i].discount_start_hour,
                        product[i].discount_start_min,
                        product[i].discount_end_year,
                        product[i].discount_end_month,
                        product[i].discount_end_date,
                        product[i].discount_end_hour,
                        product[i].discount_end_min);
            }
            
            else if(strcmp(mkt_name,"return")==0)
                store_menu(serial_number);  //返回商品功能界面
        }
        
        fclose(infile_rank);
        
        if(k==1)
        {
            printf("\n请输入您需要的操作序号：\n1.筛选折扣商品\n2.购买商品\n3.返回上一级菜单\n4.退出\n");
            int option;
            scanf("%d", &option);
            while(option!=1&&option!=2&&option!=3&&option!=4&&option!=5&&option!=6)
            {
                printf("您的输入有误，请重新输入：\n");
                scanf("%d", &option);
            }
            switch (option)
            {
                    
                case 1:
                    ord_discount(serial_number);  //筛选折扣商品
                    break;
                case 2:
                    if(serial_number != -1)
                        user_buy(serial_number);  //加入购物车
                    user_payment(serial_number);  //付款
                    break;
                case 3:
                    store_menu(serial_number);  //返回商品功能界面
                    break;
                case 4:
                    exit(1);
                    
            }
        }
        
        if(k==0)
            printf("您输入的超市名称不存在，请重新输入:\n");
    }
}


void user_show_all(int serial_number)   //展示所有商品
{
    read_product(); //读取商品信息
    int i,j;
    i=0,j=0;
    FILE *infile_rank;
    infile_rank = fopen("Ranking.txt","w");
    for(i=0;i<product_num-1;i++)
    {
        j++;
        printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n",
               j,
               product[i].product_ID,
               product[i].product_name,
               product[i].product_market,
               product[i].price_selling,
               product[i].storage);
        
        fprintf(infile_rank,"%s\t %s\t %s\t %.2f\t %.2f\t %d\t %d\t %.2f\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
                product[i].product_ID,
                product[i].product_market,
                product[i].product_name,
                product[i].price_cost,
                product[i].price_selling,
                product[i].sales,
                product[i].storage,
                product[i].price_discount,
                product[i].discount_start_year,
                product[i].discount_start_month,
                product[i].discount_start_date,
                product[i].discount_start_hour,
                product[i].discount_start_min,
                product[i].discount_end_year,
                product[i].discount_end_month,
                product[i].discount_end_date,
                product[i].discount_end_hour,
                product[i].discount_end_min);
        
    }
    fclose(infile_rank);
    printf("\n请输入您需要的操作序号：\n1.按商品价格排序\n2.按销量排序\n3.筛选折扣商品\n4.购买商品\n5.返回上一级菜单\n6.退出\n");
    int option;
    scanf("%d",&option);
    while(option!=1&&option!=2&&option!=3&&option!=4&&option!=5&&option!=6)
    {
        printf("您的输入有误，请重新输入：\n");
        scanf("%d",&option);
    }
    
    switch (option)
    {
        case 1:
            ord_price_raise_search(serial_number);  //按价格排序
            break;
        case 2:
            ord_sales_search(serial_number);    //按销量排序
            break;
        case 3:
            ord_discount(serial_number);    //按折扣信息筛选
            break;
        case 4:
            if(serial_number != -1)
                user_buy(serial_number);    //加购物车
            user_payment(serial_number);    //付款
            break;
        case 5:
            store_menu(serial_number);  //用户功能界面
            break;
        case 6:
            exit(1);
    }
    
}


void user_show_discount(int serial_number)
{
    read_product();     //读取商品信息
    time_t t;   //读取此刻时间
    struct tm * lt;
    time (&t);  //获取Unix时间戳。
    lt = localtime (&t);    //转为时间结构。
    struct tt
    {
        int year;
        int month;
        int date;
        int hour;
        int min;
    }tt;
    tt.year=lt->tm_year+1900;
    tt.month=lt->tm_mon+1;
    tt.date=lt->tm_mday;
    tt.hour=lt->tm_hour;
    tt.min=lt->tm_min;
    int time1,time2,time3;  /*将此刻时间赋给变量*/
    
    /*判断并显示折扣商品*/
    int i,j,k;
    i=0,k=0,j=0;
    
    fflush(stdin);
    
    
    while(k==0)
    {
        if(tt.month==1||tt.month==3||tt.month==5||tt.month==7||tt.month==8||tt.month==10||tt.month==12)
            time1=(tt.year-2000)*518400+tt.month*44640+tt.date*1440+tt.hour*60+tt.min;
        else if(tt.month==2)
            time1=(tt.year-2000)*518400+tt.month*40320+tt.date*1440+tt.hour*60+tt.min;
        else
            time1=(tt.year-2000)*518400+tt.month*43200+tt.date*1440+tt.hour*60+tt.min;
        
        /*判断是否享受折扣*/
        for(i=0;i<product_num;i++)
        {
            
            if( product[i].discount_start_month==1||product[i].discount_start_month==3||
               product[i].discount_start_month==5||product[i].discount_start_month==7||
               product[i].discount_start_month==8||product[i].discount_start_month==10||
               product[i].discount_start_month==12)
                time2=(product[i].discount_start_year-2000)*518400+product[i].discount_start_month*44640+
                product[i].discount_start_date*1440+product[i].discount_start_hour*360+product[i].discount_start_min*60;
            else if(product[i].discount_start_month==2)
                time2=(product[i].discount_start_year-2000)*518400+product[i].discount_start_month*40320+
                product[i].discount_start_date*1440+product[i].discount_start_hour*360+product[i].discount_start_min*60;
            else
                time2=(product[i].discount_start_year-2000)*518400+product[i].discount_start_month*43200+
                product[i].discount_start_date*1440+product[i].discount_start_hour*360+product[i].discount_start_min*60;
            if( product[i].discount_end_month==1||product[i].discount_end_month==3||
               product[i].discount_end_month==5||product[i].discount_end_month==7||
               product[i].discount_end_month==8||product[i].discount_end_month==10||
               product[i].discount_end_month==12)
                time3=(product[i].discount_end_year-2000)*518400+product[i].discount_end_month*44640+
                product[i].discount_end_date*1440+product[i].discount_end_hour*360+product[i].discount_end_min*60;
            else if(product[i].discount_end_month==2)
                time3=(product[i].discount_end_year-2000)*518400+product[i].discount_end_month*40320+
                product[i].discount_end_date*1440+product[i].discount_end_hour*360+product[i].discount_end_min*60;
            else
                time3=(product[i].discount_end_year-2000)*518400+product[i].discount_end_month*43200+
                product[i].discount_end_date*1440+product[i].discount_end_hour*360+product[i].discount_end_min*60;/*计算时间总量，进行比较是否在折扣期*/
            
            if(time2<=time1&&time1<=time3)
            {
                k=1;
                j++;
                printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n 折扣时间 %d:%d:%d:%d:%d--%d:%d:%d:%d:%d\n",
                       j,
                       product[i].product_ID,
                       product[i].product_name,
                       product[i].product_market,
                       product[i].price_selling,
                       product[i].storage,
                       product[i].discount_start_year,
                       product[i].discount_start_month,
                       product[i].discount_start_date,
                       product[i].discount_start_hour,
                       product[i].discount_start_min,
                       product[i].discount_end_year,
                       product[i].discount_end_month,
                       product[i].discount_end_date,
                       product[i].discount_end_hour,
                       product[i].discount_end_min);
            }
        }
        
        if (k==1)
        {
            printf("\n请输入您需要的操作序号：\n1.按商品价格排序\n2.按销量排序\n3.购买商品\n4.返回上一级菜单\n5.退出\n");
            int option;
            scanf("%d",&option);
            while(option!=1&&option!=2&&option!=3&&option!=4&&option!=5)
            {
                printf("您的输入有误，请重新输入");
                scanf("%d",&option);
            }
            switch (option)
            {
                case 1:
                    ord_price_raise_search(serial_number);
                    break;
                case 2:
                    ord_sales_search(serial_number);
                    break;
                case 3:
                    if(serial_number != -1)
                        user_buy(serial_number);
                    user_payment(serial_number);
                    
                    break;
                case 4:
                    store_menu(serial_number);
                    break;
                case 5:
                    exit(1);
                    
            }
        }
    }
}


void ord_discount(int serial_number) //过滤是否有折扣
{
    read_admin();   //读取管理员信息
    int ord_discount_num;
    int i=0;
    FILE*infile;
    infile=fopen("Ranking.txt","r");
    if(infile==NULL)
    {
        printf("failed to open the file.\n");
        exit(1);
    }
    
    while(!feof(infile))
    {
        fscanf(infile,"%s %s %s %f %f %d %d %f %d %d %d %d %d %d %d %d %d %d",
               product[i].product_ID,
               product[i].product_market,
               product[i].product_name,
               &product[i].price_cost,
               &product[i].price_selling,
               &product[i].sales,
               &product[i].storage,
               &product[i].price_discount,
               &product[i].discount_start_year,
               &product[i].discount_start_month,
               &product[i].discount_start_date,
               &product[i].discount_start_hour,
               &product[i].discount_start_min,
               &product[i].discount_end_year,
               &product[i].discount_end_month,
               &product[i].discount_end_date,
               &product[i].discount_end_hour,
               &product[i].discount_end_min);
        i++;
    }
    fclose(infile);
    ord_discount_num=i;
    
    time_t t;
    struct tm * lt;
    time (&t);//获取Unix时间戳。
    lt = localtime (&t);//转为时间结构。
    struct tt
    {
        int year;
        int month;
        int date;
        int hour;
        int min;
    }tt;
    tt.year=lt->tm_year+1900;
    tt.month=lt->tm_mon+1;
    tt.date=lt->tm_mday;
    tt.hour=lt->tm_hour;
    tt.min=lt->tm_min;
    int time1,time2,time3;/*将此刻时间赋给变量*/
    
    /*判断并显示折扣商品*/
    int j,k;
    i=0,k=0,j=0;
    
    fflush(stdin);
    if(tt.month==1||tt.month==3||tt.month==5||tt.month==7||tt.month==8||tt.month==10||tt.month==12)
        time1=(tt.year-2000)*518400+tt.month*44640+tt.date*1440+tt.hour*60+tt.min;
    else if(tt.month==2)
        time1=(tt.year-2000)*518400+tt.month*40320+tt.date*1440+tt.hour*60+tt.min;
    else
        time1=(tt.year-2000)*518400+tt.month*43200+tt.date*1440+tt.hour*60+tt.min;
    
    /*判断是否享受折扣*/
    for(i=0;i<ord_discount_num;i++)
    {
        
        if( product[i].discount_start_month==1||product[i].discount_start_month==3||
           product[i].discount_start_month==5||product[i].discount_start_month==7||
           product[i].discount_start_month==8||product[i].discount_start_month==10||
           product[i].discount_start_month==12)
            time2=(product[i].discount_start_year-2000)*518400+product[i].discount_start_month*44640+
            product[i].discount_start_date*1440+product[i].discount_start_hour*360+product[i].discount_start_min*60;
        else if(product[i].discount_start_month==2)
            time2=(product[i].discount_start_year-2000)*518400+product[i].discount_start_month*40320+
            product[i].discount_start_date*1440+product[i].discount_start_hour*360+product[i].discount_start_min*60;
        else
            time2=(product[i].discount_start_year-2000)*518400+product[i].discount_start_month*43200+
            product[i].discount_start_date*1440+product[i].discount_start_hour*360+product[i].discount_start_min*60;
        if( product[i].discount_end_month==1||product[i].discount_end_month==3||
           product[i].discount_end_month==5||product[i].discount_end_month==7||
           product[i].discount_end_month==8||product[i].discount_end_month==10||
           product[i].discount_end_month==12)
            time3=(product[i].discount_end_year-2000)*518400+product[i].discount_end_month*44640+
            product[i].discount_end_date*1440+product[i].discount_end_hour*360+product[i].discount_end_min*60;
        else if(product[i].discount_end_month==2)
            time3=(product[i].discount_end_year-2000)*518400+product[i].discount_end_month*40320+
            product[i].discount_end_date*1440+product[i].discount_end_hour*360+product[i].discount_end_min*60;
        else
            time3=(product[i].discount_end_year-2000)*518400+product[i].discount_end_month*43200+
            product[i].discount_end_date*1440+product[i].discount_end_hour*360+product[i].discount_end_min*60;/*计算时间总量，进行比较是否在折扣期*/
        
        if(time2<=time1&&time1<=time3)
        {
            k=1;
            j++;
            printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n 折扣时间 %d:%d:%d:%d:%d--%d:%d:%d:%d:%d\n",
                   j,
                   product[i].product_ID,
                   product[i].product_name,
                   product[i].product_market,
                   product[i].price_selling,
                   product[i].storage,
                   product[i].discount_start_year,
                   product[i].discount_start_month,
                   product[i].discount_start_date,
                   product[i].discount_start_hour,
                   product[i].discount_start_min,
                   product[i].discount_end_year,
                   product[i].discount_end_month,
                   product[i].discount_end_date,
                   product[i].discount_end_hour,
                   product[i].discount_end_min);
        }
    }
    
    if (k==1)
    {
        printf("\n请输入您需要的操作序号：\n1.购买商品\n2.返回上一级菜单\n3.退出\n");
        int option;
        scanf("%d",&option);
        if(option!=1&&option!=2&&option!=3)
            printf("您的输入有误，请重新输入");
        else
            switch (option)
        {
            case 1:
                if(serial_number != -1)
                    user_buy(serial_number);    //加购物车
                break;
            case 2:
                store_menu(serial_number);  //用户功能界面
                break;
            case 3:
                exit(1);
                
        }
    }
    else if (k == 0)
    {
        printf("\n无折扣商品。自动返回商品查询菜单\n");
        store_menu(serial_number);  //用户功能界面
    }
    
}


void read_user()    //读取用户信息
{
    FILE *userInformation;
    int i=0;
    if((userInformation = fopen("user.txt", "r")) == NULL)  //打开文件user并检查是否打开成功
    {
        printf("\n文件数据出现问题，请检查源文件。\n");
        exit(1);
    }
    while(!feof(userInformation))   //读取文件
    {
        fscanf( userInformation, "%s %s %s %s %s %s %s %f",
               user[i].userID, user[i].userCode,
               user[i].userName, user[i].userSex,
               user[i].userPhone, user[i].userMail,
               user[i].userAddress, &user[i].userBalance);
        i++;
        
    }
    fclose(userInformation);
    user_num=i;
}


void read_admin()   //读取管理员信息
{
    FILE *adminInformation;
    int i=0;
    if((adminInformation = fopen("admin.txt", "r")) == NULL)  //打开文件user并检查是否打开成功
    {
        printf("\n文件数据出现问题，请检查源文件。\n");
        exit(1);
    }
    while(!feof(adminInformation))   //读取文件
    {
        fscanf( adminInformation, "%s %s %s %s %s",
               admin[i].adminID, admin[i].adminCode,
               admin[i].adminName, admin[i].adminMarket,
               admin[i].adminMail);
        i++;
        
    }
    fclose(adminInformation);
    admin_num=i;
}

void read_product() //读取商品信息
{
    int i=0;
    FILE*infile;
    infile=fopen("product.txt","r");
    if(infile==NULL)
    {
        printf("failed to open the file.\n");
        exit(1);
    }
    while(!feof(infile))
    {
        fscanf(infile,"%s %s %s %f %f %d %d %f %d %d %d %d %d %d %d %d %d %d %s",
               product[i].product_ID,
               product[i].product_market,
               product[i].product_name,
               &product[i].price_cost,
               &product[i].price_selling,
               &product[i].sales,
               &product[i].storage,
               &product[i].price_discount,
               &product[i].discount_start_year,
               &product[i].discount_start_month,
               &product[i].discount_start_date,
               &product[i].discount_start_hour,
               &product[i].discount_start_min,
               &product[i].discount_end_year,
               &product[i].discount_end_month,
               &product[i].discount_end_date,
               &product[i].discount_end_hour,
               &product[i].discount_end_min,
               product[i].season
               );
        i++;
    }
    fclose(infile);
    product_num=i;
}


int isEmail(char *email) //检查邮箱地址
{
    char *p;
    p=strstr(email,"@");
    if(!p)return 0;
    if (!(p-email))return 0;
    if(!(strstr(p,".")-p))return 0;
    p=strstr(p,".");
    if(*(p+1)=='\0')return 0;
    return 1;
}


void user_buy(int serial_number)
{
    FILE *userbuyfile;
    char p_id[20];
    int a, b, num, mm=1, qq=1, total1;
    int time1,time2,time3;
    read_product(); //读取商品信息
    read_user();    //读取用户信息
    b = serial_number;
    if(serial_number==-1)
    {
        printf("\n您目前未登录，请登录后再购买商品\n");
        primary_menu();
    }
    else
        while(qq==1)
        {
            printf("\n请输入您要购买的商品ID：");
            scanf("%s",p_id);
            total1=product_num;
            for(a=0;a<total1;a++)
            {
                if(strcmp(p_id,product[a].product_ID)==0)
                    break;
            }//根据商品编号,定位商品信息
            if(a==total1)
            {
                printf("\n您输入的商品编号有误，请重新输入");
                qq=1;
            }
            else
                qq=0;
        }
    time_t t;
    struct tm * lt;
    time (&t);//获取Unix时间戳。
    lt = localtime (&t);//转为时间结构。
    tt.year=lt->tm_year+1900;
    tt.month=lt->tm_mon+1;
    tt.date=lt->tm_mday;
    tt.hour=lt->tm_hour;
    tt.min=lt->tm_min;
    
    if(tt.month==1||tt.month==3||tt.month==5||tt.month==7||tt.month==8||tt.month==10||tt.month==12)
        time1=(tt.year-2000)*518400+tt.month*44640+tt.date*1440+tt.hour*60+tt.min;
    else if(tt.month==2)
        time1=(tt.year-2000)*518400+tt.month*40320+tt.date*1440+tt.hour*60+tt.min;
    else
        time1=(tt.year-2000)*518400+tt.month*43200+tt.date*1440+tt.hour*60+tt.min;
    if( product[a].discount_start_month==1||product[a].discount_start_month==3||
       product[a].discount_start_month==5||product[a].discount_start_month==7||
       product[a].discount_start_month==8||product[a].discount_start_month==10||
       product[a].discount_start_month==12)
        time2=(product[a].discount_start_year-2000)*518400+product[a].discount_start_month*44640+
        product[a].discount_start_date*1440+product[a].discount_start_hour*360+product[a].discount_start_min*60;
    else if(product[a].discount_start_month==2)
        time2=(product[a].discount_start_year-2000)*518400+product[a].discount_start_month*40320+
        product[a].discount_start_date*1440+product[a].discount_start_hour*360+product[a].discount_start_min*60;
    else
        time2=(product[a].discount_start_year-2000)*518400+product[a].discount_start_month*43200+
        product[a].discount_start_date*1440+product[a].discount_start_hour*360+product[a].discount_start_min*60;
    if( product[a].discount_end_month==1||product[a].discount_end_month==3||
       product[a].discount_end_month==5||product[a].discount_end_month==7||
       product[a].discount_end_month==8||product[a].discount_end_month==10||
       product[a].discount_end_month==12)
        time3=(product[a].discount_end_year-2000)*518400+product[a].discount_end_month*44640+
        product[a].discount_end_date*1440+product[a].discount_end_hour*360+product[a].discount_end_min*60;
    else if(product[a].discount_end_month==2)
        time3=(product[a].discount_end_year-2000)*518400+product[a].discount_end_month*40320+
        product[a].discount_end_date*1440+product[a].discount_end_hour*360+product[a].discount_end_min*60;
    else
        time3=(product[a].discount_end_year-2000)*518400+product[a].discount_end_month*43200+
        product[a].discount_end_date*1440+product[a].discount_end_hour*360+product[a].discount_end_min*60;/*计算时间总量，进行比较是否在折扣期*/
    
    if(time2<=time1&&time1<=time3)
    {
        printf("\n当前时间为%d年%d月%d日%d时%d分\n",tt.year,tt.month,tt.date,tt.hour,tt.min);
        product[a].price_selling=product[a].price_discount;
        printf("\n您选择的商品正处于折扣期，折扣后价钱为%6.2f\n",product[a].price_selling);
    }
    
    /*判断是否享受折扣*/
    while(mm==1)
    {
        
        printf("\n请输入你要购买此商品的数量：\n");
        scanf("%d",&num);
        cus_unorder[a].g_total=product[a].price_selling*num;
        if(num<1)
        {
            printf("\n请输入正确的商品数量\n");
            mm=1;
        }
        else if(num>product[a].storage)
        {
            printf("\n商品库存为%d，你要购买的数量为%d",product[a].storage,num);
            printf("\n商品库存不足，请重新选择\n");
            mm=1;
            
        }
        else if (cus_unorder[a].g_total>user[b].userBalance)
        {
            printf("\n你的余额为%6.2f,商品总价为%6.2f",user[b].userBalance,cus_unorder[a].g_total);
            printf("\n您的余额不足以支付此商品，请重新选择\n");
            mm=1;
        }
        else
            mm=0;
    }
    
    char plus[]="购物车.txt";
    char filename[100];
    strcpy(filename,user[b].userID);
    strcat(filename,plus);
    userbuyfile=fopen(filename,"a");
    if(userbuyfile==NULL)
    {
        printf("\nFailed to open the file.\n");
        exit(1);
    }
    sprintf(cus_unorder[a].o_time,"%d:%d:%d:%d:%d",tt.year,tt.month,tt.date,tt.hour,tt.min);/*整数型时间转换为字符串型时间*/
    
    cus_unorder[a].g_number=num;/*将数量赋值*/
    strcpy(cus_unorder[a].o_id,product[a].product_market);
    strcat(cus_unorder[a].o_id,user[b].userID);
    strcat(cus_unorder[a].o_id,cus_unorder[a].o_time);/*生成订单编号*/
    fprintf(userbuyfile,"%s %s %s %s %s %d %5.2f %5.2f\n",
            cus_unorder[a].o_id,
            cus_unorder[a].o_time,
            product[a].product_market,
            product[a].product_ID,
            product[a].product_name,
            cus_unorder[a].g_number,
            product[a].price_selling,
            cus_unorder[a].g_total
            );/*将商品信息录入购物车*/
    fclose(userbuyfile);
    printf("\n已将此物品成功添加到购物车\n");
}


void user_payment(int serial_number)    //付款
{
    char plus[]="订单.txt";
    char filename[100];
    char pplus[]="购物车.txt";
    char ffilename[100];
    FILE *userbuyfile;
    FILE *userpayfile;
    FILE *infile;
    FILE *outfile;
    FILE *userfile;
    int option,option1,mm=0,nn,b,a,i,j;
    if(serial_number==-1)
    {
        printf("\n您目前未登录，请登录后再购买商品\n");
        primary_menu();
    }
    else
        
        while(mm==0)
        {
            nn=1;
            printf("\n请输入数字执行下一步操作：");
            printf("\n1:继续购物");
            printf("\n2:清空购物车") ;
            printf("\n3:购物车结账");
            printf("\n4:返回上一级");
            printf("\n5:退出\n");
            scanf("%d",&option) ;
            switch(option)
            {
                case 1:
                    store_menu(serial_number);
                    mm=0;
                    break;
                case 2:
                    read_user();
                    
                    b = serial_number;
                    
                    strcpy(ffilename,user[b].userID);
                    strcat(ffilename,pplus);
                    userbuyfile=fopen(ffilename,"w");
                    fclose(userbuyfile);
                    printf("\n购物车已清空\n");
                    printf("\n请继续您的选择\n");
                    mm=0;
                    break;
                case 3:
                    read_user();
                    b = serial_number;
                    strcpy(ffilename,user[b].userID);
                    strcat(ffilename,pplus);
                    userbuyfile=fopen(ffilename,"r");
                    
                    if(userbuyfile==NULL)
                    {
                        printf("\nfailed to open the file.");
                        exit(1);
                    }
                    a=0;
                    while(!feof(userbuyfile))
                    {
                        fscanf(userbuyfile,"%s %s %s %s %s %d %f %f\n",
                               cus_order[a].o_id,
                               cus_order[a].o_time,
                               cus_order[a].g_s_id,
                               cus_order[a].g_id,
                               cus_order[a].g_name,
                               &cus_order[a].g_number,
                               &cus_order[a].g_price,
                               &cus_order[a].g_total
                               );
                        a++;
                    }/*读取用户购物车信息*/
                    
                    fclose(userbuyfile);
                    printf("\n您的购物车信息为：\n");
                    for(i=0;i<a;i++)
                        printf("%s\t%s\t%s\t%s\t%s\t%d\t%5.2f\t%5.2f\n",
                               cus_order[i].o_id,
                               cus_order[i].o_time,
                               cus_order[i].g_s_id,
                               cus_order[i].g_id,
                               cus_order[i].g_name,
                               cus_order[i].g_number,
                               cus_order[i].g_price,
                               cus_order[i].g_total
                               );
                    
                    /*向顾客展示购物车信息*/
                    for(i=0;i<a;i++)
                    {
                        cus_order[i+1].g_all=cus_order[i].g_all+cus_order[i].g_total;
                    }
                    printf("\n您的余额为%6.2f元,商品合计为%6.2f元",user[b].userBalance,cus_order[i].g_all);
                    printf("\n请输入数字做出下一步选择：");
                    printf("\n1:确认购买");
                    printf("\n2:取消购买，返回上一级\n");
                    scanf("%d",&option1);
                    if(option1==2)
                    {
                        break;
                    }
                    else if(option1!=1)
                    {
                        printf("\n输入错误，自动返回上一级");
                        break;
                    }
                    if(user[b].userBalance<cus_order[i].g_all)
                    {
                        printf("\n您的余额为%6.2f元,商品合计为%6.2f元",user[b].userBalance,cus_order[i].g_all);
                        printf("\n您的余额不足以支付全部商品，请重新选择");
                        mm=0;
                        break;
                    }
                    else
                        
                        printf("\n您的余额为%6.2f元,商品合计为%6.2f元",user[b].userBalance,cus_order[i].g_all);
                    printf("\n购买成功，你的余额还剩余%6.2f",user[b].userBalance-cus_order[i].g_all);
                    userbuyfile=fopen(ffilename,"w");/*购物成功后清空购物车*/
                    
                    user[b].userBalance=user[b].userBalance-cus_order[i].g_all;
                    if((userfile = fopen("user.txt", "w")) == NULL)  //打开文件user并检查是否打开成功
                    {
                        printf("\n文件数据出现问题，请检查源文件。\n");
                        exit(1);
                    }
                    for(i=0;i<user_num;i++)
                    {
                        fprintf(userfile, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%5.2f\n",
                                user[i].userID, user[i].userCode,
                                user[i].userName, user[i].userSex,
                                user[i].userPhone, user[i].userMail,
                                user[i].userAddress, user[i].userBalance);
                    }
                    fclose(userfile);/*更新顾客余额信息*/
                    
                    strcpy(filename,user[b].userID);
                    strcat(filename,plus);
                    userpayfile=fopen(filename,"a");
                    
                    if(userpayfile==NULL)
                    {
                        printf("\nfailed to open the file.\n");
                        exit(1);
                    }
                    
                    for(i=0;i<a;i++)
                    {
                        
                        fprintf(userpayfile,"%s\t%s\t%s\t%s\t%s\t%d\t%5.2f\t%5.2f\n",
                                cus_order[i].o_id,
                                cus_order[i].o_time,
                                cus_order[i].g_s_id,
                                cus_order[i].g_id,
                                cus_order[i].g_name,
                                cus_order[i].g_number,
                                cus_order[i].g_price,
                                cus_order[i].g_total
                                );
                        
                    }/*将购物车信息录入到订单信息*/
                    fclose(userpayfile);
                    
                    read_product();
                    for(i=0;i<a;i++)
                    {
                        for(j=0;j<product_num;j++)
                        {
                            if(strcmp(cus_order[i].g_id,product[j].product_ID)==0)
                            {
                                product[j].storage=product[j].storage-cus_order[i].g_number;/*计算商品库存*/
                                product[j].sales=product[j].sales+cus_order[i].g_number;/*计算商品销量*/
                                
                            }
                        }
                    }
                    infile=fopen("product.txt","w");
                    if(infile==NULL)
                    {
                        printf("\nfailed to open the file.\n");
                        exit(1);
                    }
                    
                    for(i=0;i<product_num;i++)
                    {
                        fprintf(infile,"%s\t%s\t%s\t%5.2f\t%5.2f\t%d\t%d\t%5.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
                                product[i].product_ID,
                                product[i].product_market,
                                product[i].product_name,
                                product[i].price_cost,
                                product[i].price_selling,
                                product[i].sales,
                                product[i].storage,
                                product[i].price_discount,
                                product[i].discount_start_year,
                                product[i].discount_start_month,
                                product[i].discount_start_date,
                                product[i].discount_start_hour,
                                product[i].discount_start_min,
                                product[i].discount_end_year,
                                product[i].discount_end_month,
                                product[i].discount_end_date,
                                product[i].discount_end_hour,
                                product[i].discount_end_min,
                                product[i].season);
                        
                    }/*更新商品信息中的销量和库存信息*/
                    fclose(infile);
                    
                    for(i=0;i<a;i++)
                    {
                        strcpy(filename,cus_order[i].g_s_id);
                        strcat(filename,plus);
                        outfile=fopen(filename,"a");
                        if(outfile==NULL)
                        {
                            printf("\nfailed to open the file.\n");
                            exit(1);
                        }
                        for(j=0;j<product_num-1;j++)
                        {
                            if(strcmp(cus_order[i].g_id,product[j].product_ID)==0)
                            {
                                cus_order[i].g_sales=product[j].sales;/*记录商品销量*/
                                cus_order[i].g_benefit=cus_order[i].g_number*(cus_order[i].g_price-product[j].price_cost);/*计算商品利润*/
                                
                            }
                        }
                        fprintf(outfile,"%s\t%s\t%s\t%s\t%d\t%5.2f\t%5.2f\t%d\t%5.2f\t%s\t%s\t%s\t%s\t%s\t%s\n",
                                cus_order[i].o_id,
                                cus_order[i].o_time,
                                cus_order[i].g_id,
                                cus_order[i].g_name,
                                cus_order[i].g_number,
                                cus_order[i].g_price,
                                cus_order[i].g_total,
                                cus_order[i].g_sales,
                                cus_order[i].g_benefit,
                                user[b].userID,
                                user[b].userName,
                                user[b].userSex,
                                user[b].userPhone,
                                user[b].userMail,
                                user[b].userAddress
                                );
                        
                    }/*将顾客订单信息录入到管理员订单信息*/
                    printf("\n请继续您的选择\n");
                    mm=0;
                    break;
                case 4:
                    store_menu(serial_number);
                    break;
                case 5:
                    exit(1);
                    
                default:
                    printf("\n错误序号，请重新输入\n");
                    break;
                    
                    
            }
        }
}

void user_change_mail(int serial_number)    //修改用户邮箱
{
    int i = 0, j = 0, total;
    char inputEmail1[81];
    char inputEmail2[81];
    FILE *userChangeEmail;
    userChangeEmail = fopen("user.txt","r");    //打开user文件
    
    if( userChangeEmail == NULL )
    {
        printf("\n文件数据出现问题，请检查源文件。\n");
        exit(1);
    }
    
    while(!feof(userChangeEmail))   //读取user文件
    {
        fscanf(userChangeEmail, "%s %s %s %s %s %s %s %f ",user[i].userID, user[i].userCode,
               user[i].userName, user[i].userSex,
               user[i].userPhone, user[i].userMail,
               user[i].userAddress, &user[i].userBalance);
        i++;
        total++;    //每读一行加1，最后读完就是user文件的总行数
    }
    
    while(1)
    {
        printf("请按照xxx@xxx.xxx的格式输入您的新邮箱：\n");
        scanf("%s",inputEmail1);
        
        if(isEmail(inputEmail1))
        {
            printf("请再次输入以确认：\n");
            scanf("%s", inputEmail2);
            if(strcmp(inputEmail1,inputEmail2) == 0)
            {
                strcpy(user[serial_number].userMail, inputEmail1);   //改，让原来的邮箱变成新输入的邮箱
                userChangeEmail = fopen("user.txt","w");    //写入
                for(j=0; j<total ;j++)
                {
                    fprintf(userChangeEmail,"%s %s %s %s %s %s %s %.2f \n",user[j].userID, user[j].userCode,
                            user[j].userName, user[j].userSex,
                            user[j].userPhone, user[j].userMail,
                            user[j].userAddress, user[j].userBalance);
                }
                printf("\n修改成功!\n");
                break;
            }
            else
                printf("两次输入信息不同，请重新输入：\n");
        }
        else
            printf("错误的邮箱格式，请按照xxx@xxx.xxx输入：\n");
    }
    fclose(userChangeEmail);
}


void user_change_code(int serial_number)    //修改用户密码
{
    int i = 0, j = 0, total;
    char inputCode1[81];
    char inputCode2[81];
    
    FILE *userChangeCode;
    userChangeCode = fopen("user.txt","r");    //打开user文件
    if( userChangeCode == NULL )
    {
        printf("\n文件数据出现问题，请检查源文件。\n");
        exit(1);
    }
    while(!feof(userChangeCode))   //读取user文件
    {
        fscanf(userChangeCode, "%s %s %s %s %s %s %s %f ",user[i].userID, user[i].userCode,
               user[i].userName, user[i].userSex,
               user[i].userPhone, user[i].userMail,
               user[i].userAddress, &user[i].userBalance);
        i++;
        total++;    //每读一行加1，最后读完就是user文件的总行数
    }
    
    while(1)
    {
        printf("请输入您的新密码：\n");
        scanf("%s", inputCode1);
        printf("请再次输入以确认：\n");
        scanf("%s", inputCode2);
        if(strcmp(inputCode1,inputCode2) == 0)
        {
            strcpy(user[serial_number].userCode, inputCode1);   //改
            userChangeCode = fopen("user.txt","w");    //写入
            for(j=0; j<total ;j++)
            {
                fprintf(userChangeCode,"%s %s %s %s %s %s %s %.2f \n",user[j].userID, user[j].userCode,
                        user[j].userName, user[j].userSex,
                        user[j].userPhone, user[j].userMail,
                        user[j].userAddress, user[j].userBalance);
            }
            printf("\n修改成功!\n");
            break;
        }
        else
            printf("两次输入信息不同，请重新输入：\n");
    }
    fclose(userChangeCode);
}


void user_change_phone(int serial_number)
{
    int i = 0, j = 0, total;
    char inputPhone1[81];
    char inputPhone2[81];
    FILE *userChangePhone;
    
    userChangePhone = fopen("user.txt","r");    //打开user文件
    if( userChangePhone == NULL )
    {
        printf("\n文件数据出现问题，请检查源文件。\n");
        exit(1);
    }
    while(!feof(userChangePhone))   //读取user文件
    {
        fscanf(userChangePhone, "%s %s %s %s %s %s %s %f ",user[i].userID, user[i].userCode,
               user[i].userName, user[i].userSex,
               user[i].userPhone, user[i].userMail,
               user[i].userAddress, &user[i].userBalance);
        i++;
        total++;    //每读一行加1，最后读完就是user文件的总行数
    }
    
    while(1)
    {
        printf("请输入您的新手机号：\n");
        scanf("%s", inputPhone1);
        fflush(stdin);
        while((strlen(inputPhone1)!=11)||(inputPhone1[0]<48)||(inputPhone1[0]>57)||(inputPhone1[1]<48)||(inputPhone1[1]>57)||(inputPhone1[2]<48)||(inputPhone1[2]>57)||(inputPhone1[3]<48)||(inputPhone1[3]>57)||(inputPhone1[4]<48)||(inputPhone1[4]>57)||(inputPhone1[5]<48)||(inputPhone1[5]>57)||(inputPhone1[6]<48)||(inputPhone1[6]>57)||(inputPhone1[7]<48)||(inputPhone1[7]>57)||(inputPhone1[8]<48)||(inputPhone1[8]>57)||(inputPhone1[9]<48)||(inputPhone1[9]>57)||(inputPhone1[10]<48)||(inputPhone1[10]>57))
        {
            printf("电话号码错误，请重新输入: ");
            scanf("%s",inputPhone1);
            fflush(stdin);
        }
        printf("请再次输入以确认：\n");
        scanf("%s", inputPhone2);
        if(strcmp(inputPhone1,inputPhone2) == 0)
        {
            strcpy(user[serial_number].userPhone, inputPhone1);   //改
            userChangePhone = fopen("user.txt","w");    //写入
            for(j=0; j<total ;j++)
            {
                fprintf(userChangePhone,"%s %s %s %s %s %s %s %.2f \n",user[j].userID, user[j].userCode,
                        user[j].userName, user[j].userSex,
                        user[j].userPhone, user[j].userMail,
                        user[j].userAddress, user[j].userBalance);
            }
            printf("\n修改成功!\n");
            break;
        }
        else
            printf("两次输入信息不同，请重新输入：\n");
    }
    fclose(userChangePhone);
}


void user_change_address(int serial_number)
{
    int i = 0, j = 0, total;
    char inputAddress1[81];
    char inputAddress2[81];
    FILE *userChangeAddress;
    
    userChangeAddress = fopen("user.txt","r");    //打开user文件
    if( userChangeAddress == NULL )
    {
        printf("\n文件数据出现问题，请检查源文件。\n");
        exit(1);
    }
    while(!feof(userChangeAddress))   //读取user文件
    {
        fscanf(userChangeAddress, "%s %s %s %s %s %s %s %f ",user[i].userID, user[i].userCode,
               user[i].userName, user[i].userSex,
               user[i].userPhone, user[i].userMail,
               user[i].userAddress, &user[i].userBalance);
        i++;
        total++;    //每读一行加1，最后读完就是user文件的总行数
    }
    
    while(1)
    {
        printf("请输入您的新地址：\n");
        scanf("%s", inputAddress1);
        printf("请再次输入以确认：\n");
        scanf("%s", inputAddress2);
        if(strcmp(inputAddress1,inputAddress2) == 0)
        {
            strcpy(user[serial_number].userAddress, inputAddress1);   //改
            userChangeAddress = fopen("user.txt","w");    //写入
            for(j=0; j<total ;j++)
            {
                fprintf(userChangeAddress,"%s %s %s %s %s %s %s %.2f \n",user[j].userID, user[j].userCode,
                        user[j].userName, user[j].userSex,
                        user[j].userPhone, user[j].userMail,
                        user[j].userAddress, user[j].userBalance);
            }
            
            printf("\n修改成功!\n");
            break;
        }
        else
            printf("两次输入信息不同，请重新输入：\n");
    }
    fclose(userChangeAddress);
}


void user_information(int serial_number)    //用户个人信息函数
{
    
    int i = 0,m=0;
    int choice;
    int option;   //用来解决后面需要涉及用户id的地方，因为后面我会让它等于i，就能定位到底是哪个用户，进而定位用户信息
    int total = 0;  //用户总数
    
    read_user();
    total = user_num;
    printf("请选择您需要的指令序号：\n");
    printf("1)查看个人信息\n");
    printf("2)修改个人信息\n");
    printf("3)返回上一级\n");
    scanf("%d", &choice);
    
    switch(choice)
    {
        case 1:
            printf("用户ID: %s\n用户姓名: %s\n性别: %s\n电话: %s\n密码: %s\n邮箱: %s\n收货地址: %s\n账户余额: %.2f元\n", user[serial_number].userID, user[serial_number].userName, user[serial_number].userSex, user[serial_number].userPhone, user[serial_number].userCode, user[serial_number].userMail, user[serial_number].userAddress, user[serial_number].userBalance);
            user_information(serial_number);
            break;
            
        case 2:
            while(m==0)
            {
                
                printf("请输入您需要的指令序号：\n");
                printf("1.修改电话\n");
                printf("2.修改密码\n");
                printf("3.修改邮箱\n");
                printf("4.修改地址\n");
                printf("5.返回上一级\n");
                scanf("%d", &option);
                switch(option)
                {
                    case 1:
                        user_change_phone(serial_number);   //用户更改电话
                        m=1;
                        break;
                    case 2:
                        user_change_code(serial_number);    //用户更改密码
                        m=1;
                        break;
                    case 3:
                        user_change_mail(serial_number);    //用户更改邮箱
                        m=1;
                        break;
                    case 4:
                        user_change_address(serial_number); //用户更改地址
                        m=1;
                        break;
                    case 5:
                        user_information(serial_number);    //用户信息
                        m=1;
                        break;
                    default:
                        printf("您输入了错误的指令，请重新输入： \n");
                        fflush(stdin);
                        break;
                }
            }
            user_information(serial_number);
            break;
            
        case 3:
            user_menu(serial_number);   //用户菜单
            break;
        default:
            printf("您输入了错误的指令，请重新输入： \n");
            fflush(stdin);
            break;
    }
}


void user_menu(int serial_number);   //用户菜单函数

void user_menu(int serial_number)
{
    int choice;
    system("cls");
    printf("请输入您所需要的功能的序号数字：\n");    //登录顾客的菜单
    printf("1)商品界面\n");
    printf("2)查看购物车\n");
    printf("3)查看订单信息\n");
    printf("4)个人信息\n");
    printf("5)注销，返回上一级\n");
    while(1)
    {
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                store_menu(serial_number);
                user_buy(serial_number);
                break;
            case 2:
                customer_unfinished_order(serial_number);
                user_payment(serial_number);
                break;
            case 3:
                customer_finished_order(serial_number);
                break;
            case 4:
                user_information(serial_number);
                break;
            case 5:
                primary_menu();
                break;
            default:
                printf("您输入了错误的指令，请重新输入： \n");
                fflush(stdin);
                break;
        }
    }
}


int user_login() // 顾客登录函数
{
    int m = 0;
    char code[81], ID[81];
    char inputCode[81], inputID[81];    //定义两个数组来存放用户输入的ID和密码
    char name[81], sex[81], mobile[81], email[81], area[81], balance[81];
    FILE *userID;   //文件指针
    int serial_number = 0;
    
    while(1)
    {
        printf("请输入您的用户ID: \n");
        scanf("%s", inputID);
        if((userID = fopen("user.txt","r")) == NULL)    //打开user并检查打开是否成功
        {
            printf("请检查您的数据文件。\n");
            exit(0);
        }
        
        while(fscanf(userID, "%s %s %s %s %s %s %s %s", ID, code, name, sex, mobile, email, area,balance) != EOF) //判断用户名是否存在
        {
            serial_number++;
            if(strcmp(ID, inputID) == 0)
            {
                serial_number--;
                while(1)    //判断用户密码是否正确
                {
                    printf("请输入您的密码： \n");
                    scanf("%s", inputCode);
                    if(strcmp(code, inputCode) == 0)
                    {
                        printf("登录成功！\n");
                        break;
                    }
                    else
                        printf("密码错误。\n");
                }
                
                m=1;
                break;
            }
        }
        if(m == 0)
        {
            printf("您输入的用户ID不存在。 \n");
        }
        else
            break;
    }
    fclose(userID); //关闭user文件
    return serial_number;
}


void admin_upload(int serial_number) //  管理员商品上架
{
    read_admin();
    char newName[81];
    char sellPrice[81], buyPrice[81];
    char newID[81];
    char saleVolume[81];    //销量
    char stock[81]; //库存
    char discountPrice[81];
    char discount_begin_year[81], discount_begin_month[81], discount_begin_day[81], discount_begin_hour[81],discount_begin_minute[81];
    char discount_end_year[81], discount_end_month[81], discount_end_day[81], discount_end_hour[81], discount_end_minute[81];
    int choice;
    read_product();
    int mark1 = 0, mark2 = 0;
    int i;
    printf("\n请输入您增加商品的商品名： ");
    
    do
    {
        mark1 = 0;
        scanf("%s", newName);
        for(i = 0; i < product_num; i++)
        {
            if( (strcmp(newName, product[i].product_name)==0) && (strcmp(admin[serial_number].adminMarket, product[i].product_market)==0))
                mark1 = 1;
        }
        
        if( mark1 == 1)
            printf("\n您输入的商品已存在，请重新输入:\n");
    }while(mark1 == 1);
    
    printf("\n请输入您增加商品的商品号： \n");
    
    do
    {
        mark2 = 0;
        scanf("%s", newID);
        for(i = 0; i < product_num; i++)
        {
            if( (strcmp(newID, product[i].product_ID)==0) && (strcmp(admin[serial_number].adminMarket, product[i].product_market)==0))
                mark2 = 1;
        }
        if( mark2 == 1)
            printf("\n您输入商品的商品号已存在，请重新输入:\n");
    }while(mark2 == 1);
    
    printf("\n请输入您增加商品的进货价格： ");
    scanf("%s", buyPrice);
    printf("\n请输入您增加商品的销售价格： ");
    scanf("%s", sellPrice);
    printf("\n请输入您增加商品的库存： ");
    scanf("%s", stock);
    
    printf("\n是否为该商品设置折扣？\n1. 设置折扣\n2. 无折扣\n");
    int temp_option;
    scanf("%d",&temp_option);
    switch(temp_option)
    {
        case 1:
            printf("\n请输入您增加商品的折扣价格： ");
            scanf("%s", discountPrice);
            printf("\n请输入折扣开始的年份： ");
            scanf("%s", discount_begin_year);
            printf("\n请输入折扣开始的月份： ");
            scanf("%s", discount_begin_month);
            printf("\n请输入折扣开始的日期数： ");
            scanf("%s", discount_begin_day);
            printf("\n请输入折扣开始的小时数： ");
            scanf("%s", discount_begin_hour);
            printf("\n请输入折扣开始的分钟数： ");
            scanf("%s", discount_begin_minute);
            printf("\n请输入折扣结束的年份： ");
            scanf("%s", discount_end_year);
            printf("\n请输入折扣结束的月份： ");
            scanf("%s", discount_end_month);
            printf("\n请输入折扣结束的日期数： ");
            scanf("%s", discount_end_day);
            printf("\n请输入折扣结束的小时数： ");
            scanf("%s", discount_end_hour);
            printf("\n请输入折扣开始的分钟数： ");
            scanf("%s", discount_end_minute);
            break;
        case 2:
            strcpy(discountPrice,"0");
            strcpy(discount_begin_year,"0");
            strcpy(discount_begin_month,"0");
            strcpy(discount_begin_day,"0");
            strcpy(discount_begin_hour,"0");
            strcpy(discount_begin_minute,"0");
            strcpy(discount_end_year,"0");
            strcpy(discount_end_month,"0");
            strcpy(discount_end_day,"0");
            strcpy(discount_end_hour,"0");
            strcpy(discount_end_minute,"0");
            break;
    }
    
    printf("＊您想添加商品的商品号为：\n%s\n＊您想添加商品的商品名为\n%s\n＊您想添加商品的进货价为\n%s\n＊您想添加商品的售价为\n%s\n＊您想添加商品的库存为\n%s\n＊您想添加商品的折扣价为\n%s\n＊您想添加商品的优惠开始时间为\n%s:%s:%s:%s:%s\n＊您想添加商品的优惠结束时间为\n%s/%s/%s/%s/%s\n", newID, newName, buyPrice, sellPrice, stock, discountPrice, discount_begin_year, discount_begin_month, discount_begin_day, discount_begin_hour, discount_begin_minute, discount_end_year, discount_end_month, discount_end_day, discount_end_hour, discount_end_minute);
    printf("请选择您需要的指令序号：\n");
    printf("\n1）确认添加\n");
    printf("2）修改商品号\n");
    printf("3）修改商品名\n");
    printf("4）修改进货价\n");
    printf("5）修改售价\n");
    printf("6）修改库存\n");
    printf("7）修改折扣价\n");
    printf("8）修改优惠开始时间\n");
    printf("9）修改优惠结束时间\n");
    printf("10）取消添加\n");
    scanf("%d", &choice);
    FILE *menu;
    menu = fopen("product.txt", "a");
    strcpy(saleVolume,"0");
    
    switch(choice)//记得改商家编号
    {
        case 1:
            fprintf(menu,"\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", newID, admin[serial_number].adminMarket, newName, sellPrice, buyPrice, saleVolume, stock, discountPrice, discount_begin_year, discount_begin_month,discount_begin_day, discount_begin_hour, discount_begin_minute, discount_end_year, discount_end_month, discount_end_day, discount_end_hour, discount_end_minute,"W");
            printf("请输入您所需要的功能的序号数字：\n");    //登录管理员的菜单
            printf("1)商品管理\n");
            printf("2)订单管理\n");
            printf("3)个人信息\n");
            printf("4)返回上一级\n");
            break;
        case 2:
            printf("\n请输入您更改商品的商品号： ");
            scanf("%s", newID);
            break;
        case 3:
            printf("\n请输入您更改商品的商品名： ");
            scanf("%s", newName);
            break;
        case 4:
            printf("\n请输入您更改商品的进货价： ");
            scanf("%s", sellPrice);
            break;
        case 5:
            printf("\n请输入您更改商品的售价： ");
            scanf("%s", buyPrice);
            break;
        case 6:
            printf("\n请输入您更改商品的库存： ");
            scanf("%s", stock);
            break;
        case 7:
            printf("\n请输入您更改商品的折扣价： ");
            scanf("%s", discountPrice);
            break;
        case 8:
            printf("\n请输入您更改商品的优惠开始时间： ");
            scanf("%s %s %s %s %s", discount_begin_year, discount_begin_month,discount_begin_day, discount_begin_hour, discount_begin_minute);
            break;
        case 9:
            printf("\n请输入您更改商品的优惠结束时间： ");
            scanf("%s %s %s %s %s", discount_end_year, discount_end_month, discount_end_day, discount_end_hour, discount_end_minute);
            break;
        case 10:
            printf("请输入您所需要的功能的序号数字：\n");    //登录管理员的菜单
            printf("1)商品管理\n");
            printf("2)订单管理\n");
            printf("3)个人信息\n");
            printf("4)返回上一级\n");
            break;
        default:
            printf("错误命令 请选择正确命令序号 \n");
    }
    fclose(menu);
}


void admin_change_code(int serial_number)    //修改管理员密码
{
    read_admin();
    int i = 0, j = 0, total;
    char inputCode1[81];
    char inputCode2[81];
    FILE *adminChangeCode;
    
    adminChangeCode = fopen("admin.txt","r");    //打开admin文件
    if( adminChangeCode == NULL )
    {
        printf("\n文件数据出现问题，请检查源文件。\n");
        exit(1);
    }
    while(!feof(adminChangeCode))   //读取user文件
    {
        fscanf(adminChangeCode,  "%s %s %s %s %s", admin[i].adminID, admin[i].adminCode, admin[i].adminName, admin[i].adminMarket, admin[i].adminMail);
        i++;
        total++;    //每读一行加1，最后读完就是user文件的总行数
    }
    
    while(1)
    {
        printf("请输入您的新密码：\n");
        scanf("%s", inputCode1);
        printf("请再次输入以确认：\n");
        scanf("%s", inputCode2);
        if(strcmp(inputCode1,inputCode2) == 0)
        {
            strcpy(admin[serial_number].adminCode, inputCode1);   //改
            adminChangeCode = fopen("admin.txt","w");    //写入
            for(j=0; j<total ;j++)
            {
                fprintf(adminChangeCode,  "%s %s %s %s %s", admin[j].adminID, admin[j].adminCode, admin[j].adminName, admin[j].adminMarket, admin[j].adminMail);
            }
            printf("\n修改成功!\n");
            break;
        }
        else
            printf("两次输入信息不同，请重新输入：\n");
    }
    fclose(adminChangeCode);
}


void admin_change_email(int serial_number)   //管理员修改邮箱
{
    read_admin();
    int i = 0, j = 0, total;
    char inputEmail1[81];
    char inputEmail2[81];
    FILE *adminChangeEmail;
    
    adminChangeEmail = fopen("admin.txt","r");    //打开admin文件
    if( adminChangeEmail == NULL )
    {
        printf("\n文件数据出现问题，请检查源文件。\n");
        exit(1);
    }
    
    while(!feof(adminChangeEmail))   //读取admin文件
    {
        fscanf(adminChangeEmail, "%s %s %s %s %s", admin[i].adminID, admin[i].adminCode, admin[i].adminName, admin[i].adminMarket, admin[i].adminMail);
        i++;
        total++;    //每读一行加1，最后读完就是admin文件的总行数
    }
    
    while(1)
    {
        printf("请按照xxx@xxx.xxx输入您的新邮箱：\n");
        scanf("%s",inputEmail1);
        
        if(isEmail(inputEmail1))
        {
            printf("请再次输入以确认：\n");
            scanf("%s", inputEmail2);
            if(strcmp(inputEmail1,inputEmail2) == 0)
            {
                strcpy(admin[serial_number].adminMail, inputEmail1);   //改
                adminChangeEmail = fopen("admin.txt","w");    //写入
                for(j=0; j<total ;j++)
                {
                    fprintf(adminChangeEmail,"%s %s %s %s %s", admin[j].adminID, admin[j].adminCode, admin[j].adminName, admin[j].adminMarket, admin[j].adminMail);
                }
                printf("\n修改成功!\n");
                break;
            }
            else
                printf("两次输入信息不同，请重新输入：\n");
        }
        else
            printf("错误的邮箱格式，请按照xxx@xxx.xxx输入：\n");
    }
    fclose(adminChangeEmail);
}


void admin_information(int serial_number)    //管理员个人信息函数
{
    read_admin();
    int i = 0;
    int choice;
    int option;
    int judge = 0;
    int total = 0;  //管理员总数
    char inputID[81];
    FILE *adminInformation;
    FILE *adminChangeCode;
    FILE *adminChangeEmail;
    
    if((adminInformation = fopen("admin.txt", "r")) == NULL)  //打开文件admin并检查是否打开成功
    {
        printf("\n文件数据出现问题，请检查源文件。\n");
        exit(1);
    }
    
    while(!feof(adminInformation))   //读取文件
    {
        fscanf(adminInformation, "%s %s %s %s %s", admin[i].adminID, admin[i].adminCode, admin[i].adminName, admin[i].adminMarket, admin[i].adminMail);
        i++;
        total++;
    }
    fclose(adminInformation);
    
    printf("请选择您需要的指令序号：\n");
    printf("1)查看个人信息\n");
    printf("2)修改个人信息\n");
    printf("3)返回上一级\n");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            printf("管理员ID: %s\n管理员姓名: %s\n超市名称: %s\n密码: %s\n邮箱: %s\n",
                   admin[serial_number].adminID,
                   admin[serial_number].adminName,
                   admin[serial_number].adminMarket,
                   admin[serial_number].adminCode,
                   admin[serial_number].adminMail
                   );
            admin_information(serial_number);
            break;
            
        case 2:
            printf("请输入您需要的指令序号：\n");
            printf("1.修改密码\n");
            printf("2.修改邮箱\n");
            printf("3.返回上一级\n");
            scanf("%d", &option);
            switch(option)
        {
            case 1:
                admin_change_code(serial_number);
                admin_information(serial_number);
                break;
            case 2:
                admin_change_email(serial_number);
                admin_information(serial_number);
                break;
            case 3:
                admin_information(serial_number);
                break;
            default:
                printf("您输入了错误的指令，请重新输入： \n");
                fflush(stdin);
                break;
        }
        case 3:
            admin_menu();
            break;
        default:
            printf("您输入了错误的指令，请重新输入： \n");
            fflush(stdin);
            break;
    }
}


void admin_view_order(int serial_number)//管理员查看订单情况函数
{
    read_admin();//读取管理员信息
    int i=0,j,m=0,n;
    float turnover=0;
    char storename[81];
    char filename[81];
    FILE *store_orderFile;
    strcpy(filename,admin[serial_number].adminMarket);
    strcat(filename,"订单.txt");
    store_orderFile=fopen(filename,"r");
    
    printf("您所属超市订单情况如下：\n");
    
    if(store_orderFile==NULL)//检查
    {
        printf("您所属超市还没有订单。\n");
        admin_menu();//管理员菜单函数
    }
    
    while(!feof(store_orderFile))
    {
        fscanf(store_orderFile,"%s%s%s%s%d%f%f%d%f",cus_order[i].o_id,cus_order[i].o_time,
               cus_order[i].g_id,cus_order[i].g_name,
               &cus_order[i].g_number,&cus_order[i].g_price,
               &cus_order[i].g_total,&cus_order[i].g_sales,
               &cus_order[i].g_benefit);
        fscanf(store_orderFile,"%s%s%s%s%s%s",user[i].userID,user[i].userName,user[i].userSex,
               user[i].userPhone,user[i].userMail,user[i].userAddress);
        i++;
    }
    j=i;
    printf(" 订单编号  订单时间  商品编号  商品名称  商品数量  商品单价  商品总价  商品销量  商品利润 ");
    printf(" 顾客ID  顾客姓名  顾客性别  顾客电话  顾客邮箱  顾客地址  \n");
    for(i=0;i<j-1;i++)
    {
        turnover+=cus_order[i].g_total;
        printf("%7s %7s %7s %7d %7.2f %7.2f %7d %7.2f %7s %7s %7s %7s %7s %7s\n",
               cus_order[i].o_id,
               cus_order[i].o_time,
               cus_order[i].g_name,
               cus_order[i].g_number,
               cus_order[i].g_price,
               cus_order[i].g_total,
               cus_order[i].g_sales,
               cus_order[i].g_benefit,
               user[i].userID,
               user[i].userName,
               user[i].userSex,
               user[i].userPhone,
               user[i].userMail,
               user[i].userAddress);
        
    }
    printf("本超市营业期间营业额为：%.2f\n",turnover);
    fclose(store_orderFile);
    
    while(m==0)
    {
        printf("请选择下一步操作：\n1.返回管理员菜单\n2.返回订单管理\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
                admin_menu();//管理员菜单函数
                break;
            case 2:
                admin_manage_order(serial_number);//管理员订单管理总函数
                break;
            default:
                printf("对不起，您的输入有误！\n");
                continue;
        }
        m=1;
    }
}


void admin_manage_order(int serial_number)//管理员订单管理总函数(函数首部行)
{
    read_admin();//读取管理员信息
    int c = 0,d,e = 0;
    printf("请选择下一步操作：\n1.查看所属超市购买情况及营业额\n2.统计用户订单信息\n");
    scanf("%d",&c);
    fflush(stdin);
    while(c!=1&&c!=2)
    {
        printf("对不起，您的输入有误！\n");
        scanf("%d",&c);
        fflush(stdin);
    }
    switch(c)
    {
        case 1:
            admin_view_order(serial_number);//管理员查看订单情况函数
            break;
        case 2:
            while(e==0)
            {
                printf("请选择下一步操作：\n1.按销量对订单商品进行排序\n");
                printf("2.按营业额对订单商品进行排序\n3.查看输出利润最高和最低的商品\n4.查看系统标识滞销商品及推荐进货商品（根据库存和销售情况生成）\n");
                scanf("%d",&d);
                if(d != 1 && d != 2 && d != 3 && d != 4)
                {
                    printf("对不起，您的输入有误！\n");
                    continue;
                }
                switch(d)
                {
                    case 1:
                        s_sales_ord(serial_number);
                        break;
                    case 2:
                        s_turnover_ord(serial_number);
                        break;
                    case 3:
                        s_profit_ord(serial_number);//查看输出利润最高和最低的商品函数
                        break;
                    case 4:
                        adimin_judge_sales();
                        break;
                }
                e=1;
            }
            break;
    }
}


void admin_product_management(int serial_number)
{
    read_admin();
    int option = 0;
    while(1)
    {
        system("cls");
        printf("请输入您所需要的功能的序号数字：\n");
        printf("1)商品查询\n");
        printf("2)添加商品\n");
        printf("3)返回上一级\n");
        scanf("%d",&option);
        fflush(stdin);
        while(option != 1 && option != 2 && option != 3)
        {
            printf("您的输入有误，请重新输入：\n");
            scanf("%d",&option);
            fflush(stdin);
        }
        switch(option)
        {
            case 1:
                admin_product_show(serial_number);
                break;
            case 2:
                admin_upload(serial_number);
                break;
            case 3:
                admin_menu(serial_number);
                break;
        }
        break;
    }
    
}


void admin_product_show(int serial_number)
{
    read_admin();
    read_product();//读取商品信息
    int i = 0 , j = 0;
    for(i=0;i<product_num;i++)
    {
        if(strcmp(admin[serial_number].adminMarket,product[i].product_market) == 0)
        {
            j++;//商品在本页的序号
            printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n",
                   j,
                   product[i].product_ID,
                   product[i].product_name,
                   product[i].product_market,
                   product[i].price_selling,
                   product[i].storage);
        }
    }
    printf("请输入您所需要的功能的序号数字：\n");    //登录管理员的菜单
    printf("1)商品管理\n");
    printf("2)订单管理\n");
    printf("3)个人信息\n");
    printf("4)返回上一级\n");
}


void admin_menu(int serial_number)
{
    read_admin();
    int choice;
    system("cls");
    printf("请输入您所需要的功能的序号数字：\n");    //登录管理员的菜单
    printf("1)商品管理\n");
    printf("2)订单管理\n");
    printf("3)个人信息\n");
    printf("4)注销，返回上一级\n");
    while(1)
    {
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                admin_product_management(serial_number);
                break;
            case 2:
                admin_manage_order(serial_number);
                break;
            case 3:
                admin_information(serial_number);
                break;
            case 4:
                primary_menu();
                break;
            default:
                printf("您输入了错误的指令，请重新输入： \n");
                fflush(stdin);
                break;
        }
    }
}


int admin_login() // 管理员登录函数
{
    int m = 0;
    char code[81], ID[81];
    char inputCode[81], inputID[81];    //定义两个数组来存放管理员输入的ID和密码
    char name[81], email[81], marketName[81];
    FILE *adminID;   //文件指针
    int serial_number = 0;
    while(1)
    {
        printf("请输入您的管理员ID: \n");
        scanf("%s", inputID);
        if((adminID = fopen("admin.txt","r")) == NULL)    //打开admin并检查打开是否成功
        {
            printf("请检查您的数据文件。\n");
            exit(0);
        }
        while(fscanf(adminID, "%s %s %s %s %s", ID, code, marketName, name, email) != EOF) //从admin里读取判断管理员名是否存在
        {
            serial_number++;
            if(strcmp(ID, inputID) == 0)
            {
                serial_number--;
                while(1)    //判断管理员密码是否正确
                {
                    printf("请输入您的密码： \n");
                    scanf("%s", inputCode);
                    if(strcmp(code, inputCode) == 0)
                    {
                        printf("登录成功！\n");
                        break;
                    }
                    else
                        printf("密码错误。\n");
                }
                
                m=1;
                break;
            }
        }
        if(m == 0)
        {
            printf("您输入的用户ID不存在。 \n");
        }
        else
            break;
    }
    fclose(adminID); //关闭admin文件
    return serial_number;
}


void ord_price_raise_search(int serial_number)
{
    int a,b,temp = 0;//temp为用来交换数据顺序所用的临时数据
    read_product();
    
    for(a = 0;a < product_num; a++)
    {
        for(b = 1; b< product_num; b++)
        {
            if(product[b].price_selling<product[b-1].price_selling)    //彻底交换所有信息
            {
                temp_product[0] = product[b];
                product[b] = product[b-1];
                product[b-1] = temp_product[0];
            }
        }
    }
    
    printf("按照价格从低到高排序的结果为:\n");
    int i;
    for(i = 0; i <= product_num; i++)
    {
        printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n",
               i+1,
               product[i].product_ID,
               product[i].product_name,
               product[i].product_market,
               product[i].price_selling,
               product[i].storage);
    }
    
    printf("\n请输入您需要的操作序号：\n1.按商品价格从低到高排序\n2.按销量排序\n3.筛选折扣商品\n4.购买商品\n5.返回上一级菜单\n6.退出\n");
    int option;
    scanf("%d",&option);
    if(option!=1&&option!=2&&option!=3&&option!=4&&option!=5&&option!=6)
        printf("您的输入有误，请重新输入");
    else
        switch (option)
    {
        case 1:
            ord_price_raise_search(serial_number);
            break;
        case 2:
            ord_sales_search(serial_number);
            break;
        case 3:
            ord_discount(serial_number);
            break;
        case 4:
            user_buy(serial_number);
            break;
        case 5:
            user_search_name(serial_number);
            break;
        case 6:
            exit(1);
            
    }
}


void ord_sales_search(int serial_number)
{
    
    int a,b,temp = 0;//temp为用来交换数据顺序所用的临时数据
    read_product();
    
    for(a = 0;a < product_num; a++)
    {
        for(b = 1; b< product_num; b++)
        {
            if(product[b].sales>product[b-1].sales)    //彻底交换所有信息
            {
                temp_product[0] = product[b];
                product[b] = product[b-1];
                product[b-1] = temp_product[0];
            }
        }
    }
    printf("按照销量序的结果为:\n");
    int i;
    for(i = 0; i <= product_num; i++)
    {
        printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t销量:%d\t价格:%.2f\t库存:%d\n",
               i+1,
               product[i].product_ID,
               product[i].product_name,
               product[i].product_market,
               product[i].sales,
               product[i].price_selling,
               product[i].storage);
    }
    
    printf("\n请输入您需要的操作序号：\n1.按商品价格从低到高排序\n2.按销量排序\n3.筛选折扣商品\n4.购买商品\n5.返回上一级菜单\n6.退出\n");
    int option;
    scanf("%d",&option);
    if(option!=1&&option!=2&&option!=3&&option!=4&&option!=5&&option!=6)
        printf("您的输入有误，请重新输入");
    else
        switch (option)
    {
        case 1:
            ord_price_raise_search(serial_number);
            break;
        case 2:
            ord_sales_search(serial_number);
            break;
        case 3:
            ord_discount(serial_number);
            break;
        case 4:
            user_buy(serial_number);
            break;
        case 5:
            user_search_name(serial_number);
            break;
        case 6:
            exit(1);
            
    }
}


void s_sales_ord(int serial_number)
{
    
    read_admin();
    int a,b,temp = 0;//temp为用来交换数据顺序所用的临时数据
    read_product();
    
    for(a = 0;a < product_num; a++)
    {
        for(b = 1; b< product_num; b++)
        {
            if(product[b].sales>product[b-1].sales)    //彻底交换所有信息
            {
                temp_product[0] = product[b];
                product[b] = product[b-1];
                product[b-1] = temp_product[0];
            }
        }
    }
    printf("按照销量序的结果为\n");
    int i,j=1;
    for(i = 0; i <= product_num; i++)
    {
        
        if(strcmp(product[i].product_market,admin[serial_number].adminMarket) == 0)
        {
            j++;
            printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t销量:%d\t价格:%.2f\t库存:%d\n",
                   j,
                   product[i].product_ID,
                   product[i].product_name,
                   product[i].product_market,
                   product[i].sales,
                   product[i].price_selling,
                   product[i].storage);
        }
    }
}


void s_turnover_ord(int serial_number)
{
    read_admin();
    int a,b,temp = 0;//temp为用来交换数据顺序所用的临时数据
    read_product();
    
    for(a = 0;a < product_num; a++)
    {
        for(b = 1; b< product_num; b++)
        {
            if((product[b].sales*product[b].price_selling) > (product[b-1].sales*product[b-1].price_selling))    //彻底交换所有信息
            {
                temp_product[0] = product[b];
                product[b] = product[b-1];
                product[b-1] = temp_product[0];
            }
        }
    }
    printf("按销售额排序的结果为\n");
    int i,j=1;
    for(i = 0; i <= product_num; i++)
    {
        
        if(strcmp(product[i].product_market,admin[serial_number].adminMarket) == 0)
        {
            j++;
            printf("%d.\t商品编号:%s\t商品名称:%s\t所属超市:%s\t销量:%d\t价格:%.2f\t销售额:%f\n",
                   j,
                   product[i].product_ID,
                   product[i].product_name,
                   product[i].product_market,
                   product[i].sales,
                   product[i].price_selling,
                   product[i].sales*product[i].price_selling);
        }
    }
}


void s_profit_ord(int serial_number)
{
    read_admin();
    int a,b,temp = 0;//temp为用来交换数据顺序所用的临时数据
    read_product();
    
    for(a = 0;a < product_num; a++)
    {
        for(b = 1; b< product_num; b++)
        {
            if((product[b].sales*(product[b].price_selling-product[b].price_cost)) > (product[b-1].sales*(product[b-1].price_selling-product[b-1].price_cost)))    //彻底交换所有信息
            {
                temp_product[0] = product[b];
                product[b] = product[b-1];
                product[b-1] = temp_product[0];
            }
        }
    }
    printf("经统计，利润最高及最低的商品为:\n");
    int i;
    float highest,lowest;
    highest = product[0].sales*(product[b].price_selling-product[0].price_cost);
    lowest = product[product_num].sales*(product[product_num].price_selling-product[product_num].price_cost);
    for(i = 0; i <= product_num; i++)
    {
        
        if(strcmp(product[i].product_market,admin[serial_number].adminMarket) == 0)
            if(product[b].sales*(product[b].price_selling-product[b].price_cost) == highest || product[b].sales*(product[b].price_selling-product[b].price_cost) == lowest)
            {
                printf("商品编号:%s\t商品名称:%s\t所属超市:%s\t销量:%d\t进货价:%.2f\t销售价:%.2f\t利润:%f\n",
                       product[i].product_ID,
                       product[i].product_name,
                       product[i].product_market,
                       product[i].sales,
                       product[i].price_cost,
                       product[i].price_selling,
                       product[i].sales*(product[i].price_selling-product[i].price_cost));
            }
    }
}


void adimin_judge_sales(int serial_number)//管理员判断商品滞销和进货函数
{
    read_admin();
    int j;
    read_product();
    for(j=0;j<product_num-1;j++)
    {
        if(strcmp(product[j].product_market,admin[serial_number].adminMarket)==0)
        {
            if(product[j].storage<1.5*product[j].sales)
                printf("商品%s销售情况良好，需要进货\n",product[j].product_name);
            else if (product[j].storage>1.5*product[j].sales)
                printf("商品%s销售情况较差，存在滞销\n",product[j].product_name);
        }
    }
}


void hotSale(int serial_number)//附加选项，根据季节判断商品
{
    read_product();
    time_t t;
    struct tm * lt;
    time (&t);//获取Unix时间戳。
    lt = localtime (&t);//转为时间结构。
    tt.year=lt->tm_year+1900;
    tt.month=lt->tm_mon+1;
    tt.date=lt->tm_mday;
    tt.hour=lt->tm_hour;
    tt.min=lt->tm_min;
    int i;
    if(tt.month==3||tt.month==4||tt.month==5)
    {
        printf("\n现在季节为春季，为您推荐的当季热销产品有：\n");
        for(i=0;i<product_num;i++)
        {
            
            if(strcmp("Q", product[i].season)==0)
                printf("商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n",
                       product[i].product_ID,
                       product[i].product_name,
                       product[i].product_market,
                       product[i].price_selling,
                       product[i].storage);
        }
    }
    
    if(tt.month==6||tt.month==7||tt.month==8)
    {
        printf("\n现在季节为夏季，为您推荐的当季热销产品有：\n");
        for(i=0;i<product_num;i++)
        {
            if(strcmp("W",product[i].season)==0)
                printf("商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n",
                       product[i].product_ID,
                       product[i].product_name,
                       product[i].product_market,
                       product[i].price_selling,
                       product[i].storage);
        }
    }
    
    if(tt.month==9||tt.month==10||tt.month==11)
    {
        printf("\n现在季节为秋季，为您推荐的当季热销产品有：\n");
        for(i=0;i<product_num;i++)
        {
            if(strcmp("E", product[i].season)==0)
                printf("商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n",
                       product[i].product_ID,
                       product[i].product_name,
                       product[i].product_market,
                       product[i].price_selling,
                       product[i].storage);
        }
    }
    
    if(tt.month==12||tt.month==1||tt.month==2)
    {
        printf("\n现在季节为冬季，为您推荐的当季热销产品有：\n");
        for(i=0;i<product_num;i++)
        {
            if(strcmp("R", product[i].season)==0)
                printf("商品编号:%s\t商品名称:%s\t所属超市:%s\t价格:%.2f\t库存:%d\n",
                       product[i].product_ID,
                       product[i].product_name,
                       product[i].product_market,
                       product[i].price_selling,
                       product[i].storage);
        }
    }
    
    printf("\n请输入您需要的操作序号：\n1.按商品价格排序\n2.按销量排序\n3.筛选折扣商品\n4.购买商品\n5.返回上一级菜单\n6.退出\n");
    int option;
    scanf("%d",&option);
    while(option!=1&&option!=2&&option!=3&&option!=4&&option!=5&&option!=6)
    {
        printf("您的输入有误，请重新输入：\n");
        scanf("%d",&option);
    }
    
    switch (option)
    {
        case 1:
            ord_price_raise_search(serial_number);  //按价格排序
            break;
        case 2:
            ord_sales_search(serial_number);    //按销量排序
            break;
        case 3:
            ord_discount(serial_number);    //按折扣信息筛选
            break;
        case 4:
            if(serial_number != -1)
                user_buy(serial_number);    //加购物车
            user_payment(serial_number);    //付款
            break;
        case 5:
            store_menu(serial_number);  //用户功能界面
            break;
        case 6:
            exit(1);
    }
    
}

/*main函数部分*/
int main()
{
    primary_menu(); //运行最初界面
    return 0;
}
