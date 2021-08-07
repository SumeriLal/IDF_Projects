async function getTemperature() {
    const result = await fetch("/api/temp");
    const temp = await result.json();
    console.log(temp);
    const el = document.getElementById("temp-val");
    el.innerText = temp.temp;
}

setInterval(getTemperature, 1000);

let isLedOn = false;
async function toggleLed() {
  const el = document.getElementById("led-button");
  isLedOn = !isLedOn;
  fetch("api/led", { method: "POST", body: JSON.stringify({ isLedOn }) });
  if (isLedOn) {
    el.classList.add("led-on");
    el.classList.remove("led-off");
  } else {
    el.classList.add("led-off");
    el.classList.remove("led-on");
  }
}