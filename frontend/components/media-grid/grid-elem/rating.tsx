import { Badge } from "@/components/ui/badge";
import { Star } from "lucide-react";

export function Rating({ rating }: { rating: number }) {
    return (
        <Badge variant="outline">
            <Star className="w-4 h-4 mr-1" />
            {Math.round(rating * 10) / 10}/10
        </Badge>
    );
}