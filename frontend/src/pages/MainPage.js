import React from 'react'
import axios from 'axios';
import { Link } from 'react-router-dom'
import ContentLoader from "react-content-loader"

import Parametr from "../components/Parametr";
import DatasetItem from '../components/DatasetItem';

import plus from '../assets/plus.svg';

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

	const [datasets, setDatasets] = React.useState(null);
	const [progress, setProgress] = React.useState([]);

	const [generatorParametrs, setGeneratorParametrs] = React.useState(null);
	const [isLoading, setIsLoading] = React.useState(false);
	const [isError, setIsError] = React.useState(false);

	const [selectedParametrs, setSelectedParametrs] = React.useState([]);

	const getProgres = () => {
		axios.get('https://641051b7e1212d9cc930179a.mockapi.io/progres')
		.then(({data}) => {setProgress(data)})
		.catch(e => {console.log(e)});
	}

	const getDatasets = () => {
		axios.get('https://641051b7e1212d9cc930179a.mockapi.io/datasets')
		.then(({data}) => {setDatasets(data)})
		.catch(e => {console.log(e)});
	}

	const getGeneratorParametrs = () => {
		setIsLoading(true);
		axios.get('http://127.0.0.1:8000/api/add_parameter/')
		.then(({data}) => {setGeneratorParametrs(data); setIsLoading(false);})
		.catch(e => {console.log(e); setIsLoading(false); setIsError(true);});
	}

	const deleteParametr = (id) => {
		axios.delete(`http://127.0.0.1:8000/api/add_parameter/${id}`)
		.then(() => {
			getGeneratorParametrs();
		})
		.catch(e => console.log(e));
	}
	
	const addDataset = () => {
		const data = {parameters_of_generation: selectedParametrs};
		console.log(data);
		axios.post(`http://127.0.0.1:8000/api/add_dataset`, data)
		.then(() => {
			alert('Параметры успешно отправлены на генерацию')
		})
		.catch(e => console.log(e));
	}

	React.useEffect(() => {
		getGeneratorParametrs();
		getDatasets();
		getProgres();
	}, []);

	return (
	<div className="content__wrapper">
			<div className="content__left">
				<h3>Параметры генерации</h3>
				<div className="content pb75">
						{
						!isLoading && (generatorParametrs?.length == 0) && <Link to='/add' className="content__new">Создать параметр генерации<img src={plus}/></Link>
						}
						{
						!isLoading && isError && <div className='content__new error'>Произошла ошибка при загрузке параметров</div>
						}
					<div className="content__scroll">
						{isLoading && skeleton.map((item, i) => {
							return <MyLoader key={i}/>
						})}
						{!isLoading && generatorParametrs && generatorParametrs.map((item, i) => {
							return <Parametr 
								selectedParametrs={selectedParametrs}
								setSelectedParametrs={setSelectedParametrs}
								key={i}
								dataItem={item}
								deleteParametr={() => deleteParametr(item.id)}
							/>
						})}
					</div>
					<div className="content__buttons">
						<Link to='/add' className="content__add-parametr">Добавить параметр</Link>
						<button className="content__generate" onClick={() => addDataset()}>Сгенерировать датасет</button>
					</div>
				</div>
			</div>
			<div className="content__right">
				<h3>Сгенерированный датасет</h3>
				<div className="content">
					<div className="content__scroll">
						{
							datasets && datasets.map((item , i) => {
								function findObjectById(array, id) {
									for (let i = 0; i < array.length; i++) {
									  if (array[i].id === id) {
										return array[i];
									  }
									}
									return null;
								  }
								const currentProgress = findObjectById(progress, item.id);
								return <DatasetItem key={i} id={item.id} parameters={item.parameters_of_generation} currentProgress={currentProgress}/>
							})
						}
					</div>
				</div>
			</div>
    </div>
  )
}

export default MainPage