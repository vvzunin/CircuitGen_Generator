import React from 'react'
import axios from 'axios';
import { Link } from 'react-router-dom'
import ContentLoader from "react-content-loader"

import Parametr from "../components/Parametr";
import Scheme from "../components/Scheme";
import DatasetItem from '../components/DatasetItem';

const skeleton = [0, 0, 0, 0, 0];

const dataset = [{
	id: 1
},
{
	id: 2
},
{
	id: 3
},
];

const MyLoader = (props) => (
	<ContentLoader 
	  speed={2}
	  width={"100%"}
	  height={58}
	  backgroundColor="#f7fdfc"
	  foregroundColor="#ebf4ff"
	  {...props}
	>
	  <rect x="0" y="0" rx="10" ry="10" width="100%" height="52"/>
	</ContentLoader>
  )


const MainPage = () => {

	const [generatorParametrs, setGeneratorParametrs] = React.useState(null);
	const [isLoading, setIsLoading] = React.useState(false);

	const getGeneratorParametrs = () => {
		setIsLoading(true);
		axios.get('http://127.0.0.1:8000/api/add_parameter/')
		.then(({data}) => {setGeneratorParametrs(data); setIsLoading(false);})
		.catch(e => {console.log(e); setIsLoading(false);});
	}

	const deleteParametr = (id) => {
		axios.delete(`http://127.0.0.1:8000/api/add_parameter/${id}`)
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
						{isLoading && skeleton.map((item, i) => {
							return <MyLoader key={i}/>
						})}
						{!isLoading && generatorParametrs && generatorParametrs.map((item, i) => {
							return <Parametr 
								key={i}
								dataItem={item}
								gear={false}
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
						{
							dataset && dataset.map((item , i) => {
								return <DatasetItem key={i} id={item.id}/>
							})
						}
					</div>
				</div>
			</div>
    </div>
  )
}

export default MainPage