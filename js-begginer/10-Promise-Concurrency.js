/*
Promise 并发操作工具
四个组合工具可用来并发异步操作：Promise.all()、Promise.allSettled()、Promise.any() 和 Promise.race()。
*/

// 模拟异步操作
const fetchUser = () => Promise.resolve({ id: 1, name: '张三' });
const fetchPosts = () => Promise.resolve([{ id: 1, title: '文章1' }, { id: 2, title: '文章2' }]);
const fetchComments = () => Promise.resolve([{ id: 1, text: '评论1' }]);
const slowAPI = () => new Promise(resolve => setTimeout(() => resolve('慢接口'), 2000));
const fastAPI = () => new Promise(resolve => setTimeout(() => resolve('快接口'), 500));
const failAPI = () => Promise.reject(new Error('接口失败'));

// Promise.all() - 所有Promise都成功才成功，有一个失败就失败
{
    Promise.all([fetchUser(), fetchPosts(), fetchComments()])
        .then(([user, posts, comments]) => {
            console.log('Promise.all 成功:', { user, posts, comments });
        })
        .catch(error => console.log('Promise.all 失败:', error));
}

// Promise.allSettled() - 等待所有Promise完成，不管成功失败
{
    Promise.allSettled([fetchUser(), failAPI(), fetchPosts()])
        .then(results => {
            results.forEach((result, index) => {
                if (result.status === 'fulfilled') {
                    console.log(`Promise ${index} 成功:`, result.value);
                } else {
                    console.log(`Promise ${index} 失败:`, result.reason);
                }
            });
        });
}

// Promise.any() - 任意一个Promise成功就成功，全部失败才失败
{
    Promise.any([failAPI(), slowAPI(), fastAPI()])
        .then(result => {
            console.log('Promise.any 第一个成功:', result);
        })
        .catch(error => console.log('Promise.any 全部失败:', error));
}

// Promise.race() - 第一个完成的Promise决定结果（成功或失败）
{
    Promise.race([slowAPI(), fastAPI()])
        .then(result => {
            console.log('Promise.race 第一个完成:', result);
        })
        .catch(error => console.log('Promise.race 第一个失败:', error));
}

// 实际应用场景
{
    // 并行获取多个API数据
    const loadPageData = () => {
        return Promise.all([
            fetch('https://jsonplaceholder.typicode.com/users/1').then(r => r.json()),
            fetch('https://jsonplaceholder.typicode.com/posts?userId=1').then(r => r.json())
        ]).then(([user, posts]) => ({ user, posts }));
    };

    // 超时控制
    const withTimeout = (promise, ms) => {
        const timeout = new Promise((_, reject) => 
            setTimeout(() => reject(new Error('超时')), ms)
        );
        return Promise.race([promise, timeout]);
    };

    withTimeout(fetch('https://jsonplaceholder.typicode.com/posts/1'), 3000)
        .then(response => response.json())
        .then(data => console.log('带超时的请求:', data))
        .catch(error => console.log('请求超时或失败:', error));
}