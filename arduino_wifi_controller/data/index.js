const API_URL = "http://192.168.4.22";
const gateway = `ws://192.168.4.22:81`;

const webSocket = new WebSocket(gateway);

const controlContainer = document.querySelector(".control-container");
let currButton = null;
let prevButton = null;

webSocket.onopen = () => {
  console.log("WebSocket connection established");
};

webSocket.onmessage = (event) => {
  console.log("Message from server: ", event.data);
};

document.addEventListener("keydown", (e) => {
  let btnType;
  switch (e.key) {
    case "ArrowUp":
      btnType = "forward";
      break;
    case "ArrowDown":
      btnType = "backward";
      break;
    case "ArrowLeft":
      btnType = "left";
      break;
    case "ArrowRight":
      btnType = "right";
      break;
    default:
      return;
  }
  const button = document.querySelector(`.control-btn[data-type="${btnType}"]`);
  if (!button) {
    return;
  }
  button.click();
});

controlContainer.addEventListener("click", handleButtonClick);
controlContainer.addEventListener("touchstart", handleButtonTouch); // Added touch event support
controlContainer.addEventListener("touchend", handleButtonRelease); // Added touch end support

function handleButtonClick(e) {
  const btnType = e.target.closest(".control-btn")?.dataset.type;
  if (!btnType) {
    return;
  }

  if (currButton) {
    currButton.classList.toggle("active");
  }

  currButton = e.target.closest(".control-btn");
  currButton.classList.toggle("active");
  handleCarControl(btnType);
}
// Refactored click and touch handling function
function handleButtonTouch(e) {
  const btnType = e.target.closest(".control-btn")?.dataset.type;
  if (!btnType) {
    return;
  }

  // Deselect the previous button if it's different
  if (currButton && currButton !== e.target.closest(".control-btn")) {
    currButton.classList.toggle("active");
  }

  currButton = e.target.closest(".control-btn");
  currButton.classList.toggle("active");
  // Start sending messages while the button is held down
  sendControlMessages(btnType);
}

function handleButtonRelease(e) {
  if (currButton) {
    currButton.classList.toggle("active");
  }
  currButton = null;
  // Stop sending messages when the button is released
  stopControlMessages();
}

let controlInterval;

function sendControlMessages(btnType) {
  controlInterval = setInterval(() => {
    handleCarControl(btnType);
  }, 30);
}

function stopControlMessages() {
  clearInterval(controlInterval);
}

async function handleCarControl(btnType) {
  try {
    webSocket.send(btnType);
  } catch (e) {
    console.log("Error: ", e);
  }
}
