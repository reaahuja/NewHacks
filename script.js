let countdown;
let isTimerRunning = false;
let isWorkSession = true;
// const express = require('express');
// const app = express();
// const port = 3000;

function startTimer(duration) {
  clearInterval(countdown);
  const startTime = Date.now();
  const endTime = startTime + duration * 1000;
  displayTimeLeft(duration);

  //sendMessage(false);
  countdown = setInterval(() => {
    const secondsLeft = Math.round((endTime - Date.now()) / 1000);
    if (secondsLeft < 0) {
      clearInterval(countdown);
      isTimerRunning = false;
      document.getElementById('start-btn').textContent = 'Start';
      const timerDuration = isWorkSession ? 5 * 60 : 25 * 60;
      isWorkSession = !isWorkSession;
      return;
    }
    displayTimeLeft(secondsLeft);
  }, 1000);
  //sendMessage(true);
}

function displayTimeLeft(seconds) {
  const minutes = Math.floor(seconds / 60);
  const remainderSeconds = seconds % 60;
  const display = `${minutes}:${remainderSeconds < 10 ? '0' : ''}${remainderSeconds}`;
  document.getElementById('timer-display').textContent = display;
  document.title = `PomoTodo - ${display}`;
}

document.getElementById('start-btn').addEventListener('click', () => {
  const duration = isWorkSession ? 25 * 60 : 5 * 60;
  if (!isTimerRunning) {
    startTimer(duration);
    isTimerRunning = true;
    document.getElementById('start-btn').textContent = 'Pause';
  } else {
    clearInterval(countdown);
    isTimerRunning = false;
    document.getElementById('start-btn').textContent = 'Resume';
  }
});

function addTask() {
  const input = document.getElementById('todo-input');
  if (input.value.trim() !== "" && document.querySelectorAll('#tasks li').length < 4) {
    const newTask = document.createElement('li');
    newTask.textContent = input.value;
    newTask.addEventListener('click', function() {
      this.classList.toggle('done');
    });
    const deleteBtn = document.createElement('button');
    deleteBtn.textContent = 'X';
    deleteBtn.className = 'delete-btn';
    deleteBtn.onclick = function() {
      this.parentElement.remove();
    };
    newTask.appendChild(deleteBtn);
    document.getElementById('tasks').appendChild(newTask);
    input.value = '';
  }
}

document.getElementById('todo-input').addEventListener('keyup', function(event) {
  if (event.key === 'Enter') {
    addTask();
  }
});

// function sendMessage(command){

//     app.get('/motor-movement', (req, res) => {
//         res.send(command); 
//     });

//     app.listen(port, () => {
//     console.log(`Server listening at http://localhost:${port}`);
//     });

// }

