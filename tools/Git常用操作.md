# Github相关使用
## 1.相关连接

1. [GitHub简单操作](https://www.bootcss.com/p/git-guide/)
1. [删除github文件操作](https://blog.csdn.net/weixin_43976903/article/details/86630862)
> 也可以直接进入相关文件中，直接删除对应文件，但是该操作只能一个一个地删除文件，不能批量删除文件
3. [本地添加文件至云端--操作1](https://jingyan.baidu.com/article/9989c746e35eedf648ecfe8c.html)
4. [本地添加文件至云端--操作2](https://blog.csdn.net/tangxiujiang/article/details/80463325)
5. [VS Code编辑markdown](https://www.cnblogs.com/shawWey/p/8931697.html)  
6. [Git和本地连接，需要把本地仓库(电脑)和对应的云端链接起来](https://blog.csdn.net/haochaoguo1988/article/details/82662475)

## 2.Git本地仓库和远程仓库删除文件操作简述：
- 在本地仓库打开git bash
- git pull (origin master)  :  把远程仓库拉下
- dir                     ：  查看仓库文件内容；
- git rm -r --cached <file>:  删除目标文件（可以是多个文件）
- git commit -m "text"    :   提交操作
- git push -u origin master  ：  进入远程仓库  

## 3.Git把本地仓库文件更新到远程仓库：  
备注：  该操作即可以把文件更新送到云端，也可以把新创立文件推到云端
- 在本地仓库打开git bash
- git pull:  把远程仓库拉下
- git status: 查看本地仓库的更新
- git add <file> : 增加file
- git commit -m "text"  :  提交
- git push origin master: 推上远程仓库

## 4.分支操作
1. git branch -av	           ：	查看分支情况
2. git checkout -b <本地分支robot_bim_verify> origin/<远程分支robot_bim_verify>		：		创建并切换到本地分支
3. git status 		           :	查看文件状态
4. git remote update	       :	根据远程仓库更新到本地
5. git checkout <本地分支>	    ：	 切换到本地分支
6. git push origin <远程分支>	：	 推送代码到远程分支
7. git branch -d <本地分支>	    ：	 删除本次分支

## 5.查看文件修改内容
1. 可视化方式
   1. gitk

2. 命令行方式
   1. git log filename可以查看到对应哪个操作的commit_id
   2. git show commit_id即可以看到对应的修改内容

## 6.删除远程仓库
1. 进入github对应的仓库中，选择setting，拉下最底，delete该仓库即可。

## ERROR处理
1. ! [rejected] master -> master (non-fast-forward)
   1. git pull origin master --allow-unrelated-histories
   2. 重新add/commit
   3. git push origin master
   
2. fatal: Could not read from remote repository.
   > 解决方法：更新sshkey  
   1. ssh-keygen -t rsa -C "874797636@qq.com"
   2. cat ~/.ssh/id_rsa.pub，把新密钥更新到github上面即可

3. error: failed to push some refs to 'git@github.com:TimChanCHN/Linux--JZ2440.git'
   1. 该问题是本地仓库和远程仓库的readme.md有差异，需要合并两个分支
      1. 合并分支命令：git pull --rebase origin master

4. error: cannot pull with rebase: You have unstaged changes.  
   error: please commit or stash them.
   1. 该问题是有未提交的commit，导致无法正常合并
   2. 使用下列几个命令，解决该问题：
      1. git stash     --> 暂存当前正在进行的工作
      2. 合并分支命令：git pull --rebase origin master
      3. git pull –rebase     -->   合并分支
      4. git stash pop     -->      从Git栈中读取最近一次保存的内容
   3. 后续的push等问题则会解决

5. 现象：提交的可能是文件夹，但是push后进去github/gitlab查看，会发现文件夹名称有点特别，并且点击之后不能进去，此种情况不会报error
   1. 这种现象的原因是提交的文件夹是一个本地的git仓库，即包含了.git文件
   2. 解决方法：
      1. 先删除远程仓库的文件夹： git rm -r --cached
      2. 删除本地仓库的.git文件
      3. 重新提交该文件夹即可
