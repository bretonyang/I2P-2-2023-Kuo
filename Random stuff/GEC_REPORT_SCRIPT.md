# Ideas

## Final Project

### a. Problem Definition

1. 用生活情境帶入問題動機，盡量貼近生活、使人有共鳴感
2. 正式定義問題、spec
3. 提供具體例子，以及預期得到的答案形式

### b. Idea and Approach

1. 介紹我們曾經嘗試過的方法、

### c. Code Introduction

1. Overview, and highlight how a certain code contributes
2. Introduce programming methods used
3. focus on problem solving ideas

### Recording script

"Hello everyone! Today, I am going to introduce our project, which focuses on solving the splitting bill problem. In this video, I will walk you through the problem-solving process and highlight the key computational ideas we applied."

[Code Demo]

Let's first see how our program works! Let's run the program... As you can see here, we have several commands available. We'll start with the `account` command, as you can see so far since there's no input, so no information is shown. So, let's add some data. For example, Suppose 5 people: John, Mary, Lisa, Paul, and Thomas went to Mo-Mo-Paradise and each of them has to pay 600 NTD. But John only paid 1000, Mary paid 500, Lisa paid 500, Paul paid 1000, and Thomas is a bad friend he paid nothing. Then let's use the `split` command. Yeah! As you can see here, the debtor should pay back the creditor this amount of money. For example, since Thomas paid nothing, he should pay back John and Paul 200 and 400 dollars respectively.

[Transition to the first section]

"Alright, so, the next question. How did we solve such a complex problem? As you can see in our final report, initially, the problem seemed super daunting at first glance. So, to simplify the problem, we decided to break down the problem into smaller sub-problems and solve them individually. By dividing the problem into smaller and solvable sub-problems, we could stand on a higher level of abstraction and develop the solution quite easily.

"Now, let's focus on the 'Accounts' class. One of the key functionalities we developed was the splitting mechanism. We categorized the accounts into 'debtors' and 'creditors,' based on whether they paid less or more than the expected amount. To determine how much each debtor owes each creditor, we looped through the debtors and used a while loop to distribute the debt until the debtor's balance was settled. This approach ensured that all creditors received their due and all debtors paid back what they owed.

But how do we know how many creditors have been paid when we're looping through the debtors!? To address this issue, we implemented a 'pointer' that tracks the next creditor to be paid. As we make payments to creditors, we increment the pointer's position by one. This ensures that all creditors before the pointer (i) have been paid, while all creditors after the pointer (i) remain unpaid.d"

"As you can see here. We created a main loop that allows users to interact with the program using commands such as account, split, clear, and exit. To manage the input records, since we encapsulated the functionality into an `Accounts` class, utilizing OOP principles. Each command has its own function, making the code more readable and modular. As you can see here."

"And... that concludes our presentation on the project! Thank you for watching this demo. If you have any questions or would like to discuss with us, please feel free to reach out. Have a great summer vacation!"

## [End of the video]

## Personal Report
