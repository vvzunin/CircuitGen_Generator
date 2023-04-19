import React from 'react'
import axios from 'axios';
import { Link } from 'react-router-dom'

import Parametr from "../components/Parametr";
import Scheme from "../components/Scheme";

const MainPage = () => {

	const [generatorParametrs, setGeneratorParametrs] = React.useState(null);

	console.log(generatorParametrs)

	const getGeneratorParametrs = () => {
		axios.get('https://641051b7e1212d9cc930179a.mockapi.io/generatorParametrs')
		.then(({data}) => setGeneratorParametrs(data))
		.catch(e => console.log(e));
	}

	const deleteParametr = (id) => {
		axios.delete(`https://641051b7e1212d9cc930179a.mockapi.io/generatorParametrs/${id}`)
		.then(() => {
			getGeneratorParametrs();
		})
		.catch(e => console.log(e));
	}

	React.useEffect(() => {
		getGeneratorParametrs();
	}, []);

	return (
	<div className="content__wrapper">
			<div className="content__left">
				<h3>Параметры генерации</h3>
				<div className="content pb75">
					<div className="content__scroll">
						{generatorParametrs && generatorParametrs.map((item, i) => {
							return <Parametr 
								id={item.id} 
								method={item.method}
								minInCount={item.minInCount}
								maxInCount={item.maxInCount}
								minOutCount={item.minOutCount}
								maxOutCount={item.maxOutCount}
								repeats={item.repeats}
								gear={item.gear}
								deleteParametr={() => deleteParametr(item.id)}
							/>
						})}
					</div>
					<div className="content__buttons">
						<Link to='/add' className="content__add-parametr">Добавить параметр</Link>
						<button className="content__generate">Сгенерировать датасет</button>
					</div>
				</div>
			</div>
			<div className="content__right">
				<h3>Сгенерированный датасет</h3>
				<div className="content">
					<div className="content__scroll">
						<Scheme/>
						<Scheme/>
						<Scheme/>
					</div>
				</div>
			</div>
    </div>
  )
}

export default MainPage