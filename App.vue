<template>
  <div id="app">
<!--    <img alt="Vue logo" src="./assets/logo.png">-->
<!--    <HelloWorld msg="Welcome to Your Vue.js App"/>-->

    <div class="mygutter" style="display: flex; flex-wrap: wrap">
      <div @click="playMusic(i)" class="mykey one" v-for="i in 7" :key="i">L{{ i }}</div>
      <div @click="playMusic(i + 7)" class="mykey two" v-for="i in 7" :key="i + 7">{{ i }}</div>
      <div @click="playMusic(i + 14)" class="mykey three" v-for="i in 7" :key="i + 14">H{{ i }}</div>
    </div>

    <div class="mygutter" style="padding-top: 20px">
      <label>请输入音符数
          <input v-model="num" style="width: 50px"/>
      </label>
      <button @click="genSeq">生成</button>
      <button @click="playSeq">播放</button>
      <button @click="showAns">答案</button>
    </div>
    <p>{{ answer }}</p>

  </div>
</template>

<script>
// import HelloWorld from './components/HelloWorld.vue'

export default {
  name: 'App',
  components: {
    // HelloWorld
  },
  data(){
    this.ctx = new AudioContext()
    this.sounds = [130, 147, 165, 175, 196, 220, 246,
      262, 294, 330, 349, 392, 440, 494,
      523, 587, 659, 698, 784, 880, 988]
    return {
      num: 4,
      seq: [],
      answer: ''
    }
  },
  methods: {
    playMusic(index) {
      index = index - 1

      var osc = this.ctx.createOscillator()		  //获得音频振荡器
      var g = this.ctx.createGain()				 //获得音量控制器
      osc.connect(g)						//连接音量控制器
      osc.type = 'sine'						//设置波形
      osc.frequency.value = this.sounds[index] 	  //对应钢琴不同键的不同频率
      console.log(index);
      console.log(osc.frequency.value);
      var duration = 1						//控制时间
      g.connect(this.ctx.destination)			 //连接扬声器
      g.gain.value = 0						//初始音高为0
      osc.start();							//从当前开始发生
      g.gain.linearRampToValueAtTime(0.6, this.ctx.currentTime + 0.01)	//从当前时间到0.01s后，音高从0~0.6
      osc.stop(this.ctx.currentTime + duration);						  //当前时间duration后停止
      g.gain.exponentialRampToValueAtTime(0.01, this.ctx.currentTime + duration)
    },
    genSeq() {
      this.answer = ''
      let arr = []
      for(let i = 0; i < this.num; i++){
        let n = parseInt(Math.random() * this.sounds.length)
        console.log(this.sounds.length)
        arr = arr.concat(n)
        this.seq = arr
      }
      console.log(arr)

    },
    playSeq() {
      let ref = this
      for (let i = 0; i < this.seq.length; i++){
        setTimeout(function () {
          ref.playMusic(ref.seq[i])
        }, i * 800)
      }
    },
    showAns() {
      let ans = ''
      for(let i = 0; i < this.seq.length; i++){
        if( this.seq[i] < 7 ){
          ans += "L"
        }
        if( this.seq[i] >= 14){
          ans += "H"
        }
        ans += (this.seq[i] % 7 + 1) + " "
      }
      this.answer = ans
    }
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

.one {
  background: antiquewhite;
}

.two {
  background: bisque;
}

.three {
  background: burlywood;
}

.mykey {
  border-radius: 4px;
  display: inline;
  width: 50px;
  min-width: 50px;
  height: 100px;
  min-height: 100px;
}

.mygutter > *{
  margin-left: 4px;
  margin-top: 4px;
}
</style>
