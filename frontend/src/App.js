import MainPage from "./pages/MainPage";
import { Route, Routes } from "react-router-dom"
import AddParametr from "./pages/AddParametr";

function App() {
  return (
    <div className="container">
		<h1>Генератор комбинационных схем</h1>
		<Routes>
			<Route path="/" element={<MainPage/>} />
			<Route path="/add" element={<AddParametr/>}/>
		</Routes>
    </div>
  );
}

export default App;
