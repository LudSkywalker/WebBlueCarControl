import { useState } from "react";
import BluetoothTerminal from "bluetooth-terminal";
import "./App.css";
function App() {
	const [direction, setDirection] = useState("");
	const [connected, setConnected] = useState(false);

	let terminal = new BluetoothTerminal();
	terminal.receive = (data: any) => {
		alert(data);
	};

	let toggleConnect = () => {
		if (!connected) {
			terminal.connect().then(() => {
				alert(terminal.getDeviceName() + " is connected!");
			});
		} else {
			terminal.disconnect();
			setDirection("");
		}
		setConnected(!connected);
	};
	let changeDirection = (direction: string) => {
		if (connected) {
			terminal.send(direction);
			setDirection(direction);
		}
	};
	return (
		<>
			<div className="card">
				<button onClick={toggleConnect}>
					{!connected ? "Connect" : "Disconnect"}
				</button>
			</div>
			<div className="card">
				<button onClick={() => changeDirection("!Up")}>Up</button>
				<button onClick={() => changeDirection("!Down")}>Down</button>
				<button onClick={() => changeDirection("!Left")}>Left</button>
				<button onClick={() => changeDirection("!Right")}>Right</button>
				<p>direction : {direction}</p>
			</div>
		</>
	);
}

export default App;
