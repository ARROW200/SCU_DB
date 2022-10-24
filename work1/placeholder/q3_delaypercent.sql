select distinct Shipper.CompanyName, delayRate
from Shipper,
             (select lateT.ShipVia, round((lateT.late/cast(allT.cnt as double))*100,2) as delayRate
              from (select ShipVia,count(*) as late from 'Order' where ShippedDate > RequiredDate group by ShipVia) as lateT,(select ShipVia,count(*) as cnt from 'Order' group by ShipVia) as allT
              where lateT.ShipVia = allT.ShipVia)
         as tmp
where Shipper.Id = tmp.ShipVia order by delayRate desc;