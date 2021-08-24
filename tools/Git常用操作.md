# Github相关使用
## 1.相关连接

1. [GitHub简单操作](https://www.bootcss.com/p/git-guide/)
1. [删除github文件操作](https://blog.csdn.net/weixin_43976903/article/details/86630862)
> 也可以直接进入相关文件中，直接删除对应文件，但是该操作只能一个一个地删除文件，不能批量删除文件
3. [本地添加文件至云端--操作1](https://jingyan.baidu.com/article/9989c746e35eedf648ecfe8c.html)
4. [本地添加文件至云端--操作2](https://blog.csdn.net/tangxiujiang/article/details/80463325)
5. [VS Code编辑markdown](https://www.cnblogs.com/shawWey/p/8931697.html)  
6. [Git和本地连接，需要把本地仓库(电脑)和对应的云端链接起来](https://blog.csdn.net/haochaoguo1988/article/details/82662475)

## 2.Git操作指令
1. 常见操作
- git init                       :  创建仓库
- git rev-parse HEAD             :  获取git commit id
- git pull                       :  抓起远程库最新后才能提交
- git push origin master         :  将master分支push到远程仓库
- git add file                   :  保存暂存区
- git commit file -m “commit”    :  提交git 默认分支master
- git commit --amend             :  若提交了一次，后面发现有遗漏，在git add file之后，使用该命令(默认就是上次提交的commit id)，可以把本次提交归并到上次提交中
- git rm file                    :  删除文件，再提交
- git log                        :  提交记录
- git remote -v                  :  查看远程库信息
- git status                     :  查看git状态
- git reflog                     :  记录每次的git命令
- git diff HEAD – file           :  查看工作区与版本库区别
- git checkout -– file           :  丢弃工作区的修改,未add时，实质用版本库里的版本替换工作区的版本
- git reset HEAD file            :  已经add后，暂存区修改撤销
- git clone git@github.com:账号名/项目名.git                      :  克隆远程仓库到本地库
- git remote add origin git@github.com:账号名/项目名.git          ： 关联远程库，名字origin
2. 分支操作
- git branch                     :  查看分支
   > -av                         :  同时查看远程和本地分支情况，红色字体为远程分支，绿色是本地当前活动分支，灰色为本地其他分支  
   > -v                          :  查看本地分支
- git checkout -b dev            :  创建分支dev
- git checkout master            :  切换回master分支
- git checkout -b dev origin/dev ： 拉取远程库的dev分支到本地，若无dev则重新创建一个 
- git branch -d dev              :  删除分支
- git merge dev                  :  合并分支
- git checkout -b dev origin/dev :  拉取远程库的dev分支到本地
- git merge –no-ff -m “merge with no-ff” dev                   :  冲突合并
- git branch –set-upstream dev origin/dev                      :  抓取前要本地分支与远程分支关联
3. 暂存区操作
- git stash                      :  保存工作现场  
- git stash list                 :  查看工作现场
- git stash pop                  :  恢复并删除现场的备份
- git stash apply stash@{0}      :  恢复指定现场
4. 版本回退
- git reset –hard HEAD^          :  回退上个版本
- git reset –hard commitid       :  跳转去指定版本，指定HEAD指针指向对应的代码版本，HEAD指针是在本地的代码

## 3.Git本地仓库和远程仓库删除文件操作简述：
- 在本地仓库打开git bash
- git pull (origin master)  :  把远程仓库拉下
- dir                     ：  查看仓库文件内容；
- git rm -r --cached <file>:  删除目标文件（可以是多个文件）
- git commit -m "text"    :   提交操作
- git push -u origin master  ：  进入远程仓库  

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

## 7.合并分支
> 合并分支是指把本地仓库和远程仓库内容合并，使其内容一致。如果两个仓库内容有差别，在进行某些操作时容易出错。
1. git pull
   > 获取最新代码到本地，并自动合并到当前分支，但这是直接合并，可能会把本地更新覆盖。

2. git fetch+merge
```bash
1) 查询远程版本
git remote -v
2) 获取最新代码到本地
git fetch origin branchname      // branchname:分支名称
3) 查看版本差异
git log -p master..origin/master
4) 合并最新代码到本地分支
git merge origin/master

```

## 8.放弃本地修改
1. 未git add提交代码
```bash
1) 放弃某个文件的修改
git checkout -- filename
2) 放弃全部文件的修改
git checkout .
```

2. 已经使用了git add,未使用git commit
```bash
1) 放弃某个文件的修改
git reset HEAD filename

2) 放弃全部文件的修改
git reset HEAD 
```

3. 已经使用了git commit
```bash
1) 回退到上一次commit的状态
git reset --hard HEAD^
2) 回退到任意版本的commit
git reset --hard commit id
```

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

6. 现象：更新被拒绝，因为您当前分支的最新提交落后于其对应的远程分支
   1. 合并分支即可
   2. 如果出现显示另外一个编辑器的内容(如果是git bash的话，可能是vim编辑器，在ubuntu下，可能是nano编辑器)，直接保存退出即可
