import MainPage from "./pages/MainPage";
import { Route, Routes } from "react-router-dom"
import AddParameter from "./pages/AddParameter";

function App() {
  return (
    <div className="container">
		<h1>Генератор комбинационных схем</h1>
		<Routes>
			<Route path="/" element={<MainPage/>} />
			<Route path="/add" element={<AddParameter/>}/>
		</Routes>
    </div>
  );
}

export default App;
