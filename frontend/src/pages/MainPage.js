import React from 'react'
import axios from 'axios';
import { Link } from 'react-router-dom'
import ContentLoader from "react-content-loader"

import Parametr from "../components/Parametr";
import Scheme from "../components/Scheme";

const skeleton = [0, 0, 0, 0, 0];

const MyLoader = (props) => (
	<ContentLoader 
	  speed={2}
	  width={"100%"}
	  height={58}
	  backgroundColor="#f7fdfc"
	  foregroundColor="#ebf4ff"
	  {...props}
	>
	  <rect x="0" y="0" rx="10" ry="10" width="520" height="52"/>
	</ContentLoader>
  )


const MainPage = () => {

	const [generatorParametrs, setGeneratorParametrs] = React.useState(null);
	const [isLoading, setIsLoading] = React.useState(false);

	console.log(generatorParametrs)

	const getGeneratorParametrs = () => {
		setIsLoading(true);
		axios.get('https://641051b7e1212d9cc930179a.mockapi.io/generatorParametrs')
		// .then((e) => console.log(e))
		.then(({data}) => {setGeneratorParametrs(data); setIsLoading(false);})
		.catch(e => {console.log(e); setIsLoading(false);});
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
						{isLoading && skeleton.map(item => {
							return <MyLoader/>
						})}
						{!isLoading && generatorParametrs && generatorParametrs.map((item, i) => {
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