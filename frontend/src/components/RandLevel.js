import TextField from "./TextField";

const RandLevel = () => {
    return (
      <div className="add__base">
         <TextField 
                  label="Максимальное количество уровней"
                  type="number"
                  name="maxLevel"
                  min={1}
         />
         <TextField 
                  label="Максимальное количество элементов"
                  type="number"
                  name="maxElem"
                  min={1}
         />
      </div>
    )
}

export default RandLevel;